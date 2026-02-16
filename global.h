#include <stdexcept>

template<typename B>
requires std::is_destructible_v<B>
class global
{
public:
    template<typename D = B, typename... Args>
    void init(Args&&... args) {
        static_assert(std::is_same_v<B, D> ||
                          (std::is_base_of_v<B, D> && std::has_virtual_destructor_v<B>),
                      "Type D and B must be identical or type D must be derived from B.");

        if(m_ptr != nullptr)
            throw std::runtime_error("global already initialized");
        m_ptr = new D(std::forward<Args>(args)...);
    }

    void destroy() {
        if(m_ptr == nullptr)
            throw std::runtime_error("global not initialized");
        delete m_ptr;
        m_ptr = nullptr;

    }

    B& get() {
        if(m_ptr == nullptr)
            throw std::runtime_error("global not initialized");
        return *m_ptr;
    }

    const B& get() const {
        if (!m_ptr)
            throw std::runtime_error("global not initialized");
        return *m_ptr;
    }

    bool exists() const noexcept {
        return m_ptr != nullptr;
    }

    explicit operator bool() const noexcept {
        return exists();
    }

    global() = default;

    ~global() {
        if(m_ptr != nullptr)
            delete m_ptr;
    }

    global(const global&) = delete;
    global(global&&) = delete;

    global& operator=(const global&) = delete;
    global& operator=(global&&) = delete;

private:
    B* m_ptr{nullptr};
};
