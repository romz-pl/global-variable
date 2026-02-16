#include <memory>
#include <mutex>
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
    requires std::constructible_from<D, Args...>
    void init(Args&&... args) {
        std::lock_guard<std::mutex> lock(mtx);
        if (ptr)
            throw std::runtime_error("global already initialized");
        ptr = std::make_unique<D>(std::forward<Args>(args)...);
    }

    void reset() noexcept {
        std::lock_guard<std::mutex> lock(mtx);
        ptr.reset();
    }

    B& get() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!ptr)
            throw std::runtime_error("global not initialized");
        return *ptr;
    }

    const B& get() const {
        std::lock_guard<std::mutex> lock(mtx);
        if (!ptr)
            throw std::runtime_error("global not initialized");
        return *ptr;
    }

    bool exists() const noexcept {
        std::lock_guard<std::mutex> lock(mtx);
        return ptr != nullptr;
    }

private:
    std::unique_ptr<B> ptr;
    mutable std::mutex mtx;
};
