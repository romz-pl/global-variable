#include <memory>
#include <stdexcept>

template<typename B>
requires std::is_destructible_v<B>
class global {
public:
    template<std::derived_from<B> D = B>
    void init(auto&&... args) {
        if (m_ptr) {
            throw std::runtime_error("global already initialized");
        }
        m_ptr = std::make_unique<D>(std::forward<decltype(args)>(args)...);
    }

    void reset() noexcept {
        m_ptr.reset();
    }

    B& get() {
        if (!m_ptr)
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

private:
    std::unique_ptr<B> m_ptr;
};
