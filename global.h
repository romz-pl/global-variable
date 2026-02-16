#include <memory>
#include <stdexcept>

template<typename B>
requires std::is_destructible_v<B>
class global {
public:

    global() = default;

    global(const global&) = delete;
    global(global&&) = delete;

    global& operator=(const global&) = delete;
    global& operator=(global&&) = delete;

    template<std::derived_from<B> D = B, typename... Args>
    void init(Args&&... args) {
        if (ptr)
            throw std::runtime_error("global already initialized");
        ptr = std::make_unique<D>(std::forward<Args>(args)...);
    }

    void reset() noexcept {
        ptr.reset();
    }

    B& get() {
        if (!ptr)
            throw std::runtime_error("global not initialized");
        return *ptr;
    }

    const B& get() const {
        if (!ptr)
            throw std::runtime_error("global not initialized");
        return *ptr;
    }

    bool exists() const noexcept {
        return ptr != nullptr;
    }

    explicit operator bool() const noexcept {
        return exists();
    }

private:
    std::unique_ptr<B> ptr;
};
