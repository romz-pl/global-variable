#include <stdexcept>

template<typename B>
requires std::is_destructible_v<B>
class global
{
public:
    template<std::derived_from<B> D = B>
    void init(auto&&... args) {
        if(m_ptr != nullptr)
            throw std::runtime_error("global already initialized");
        m_ptr = new D(std::forward<decltype(args)>(args)...);
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
