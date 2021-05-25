#include <type_traits>
#include <stdexcept>
#include <cassert>

template<typename B>
class global
{
public:
    template<typename D = B, typename... Args>
    void init(Args&&... args);

    void destroy();
    B& get();
    bool exists() const;

    global() = default;
    ~global();

    global(const global&) = delete;
    global(global&&) = delete;

    global& operator=(const global&) = delete;
    global& operator=(global&&) = delete;

private:
    B* m_ptr{nullptr};
};

template<typename B>
template<typename D, typename... Args>
void global<B>::init(Args&&... args) 
{
    static_assert(std::is_same_v<B, D> || std::is_base_of_v<B, D>, 
        "Type D and B must be identical or type D must be derived from B.");

    if(m_ptr != nullptr)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    else
    {
        m_ptr = new D(std::forward<Args>(args)...);
    }
}

template<typename B>
void global<B>::destroy()
{
    if(m_ptr == nullptr)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    else
    {
        delete m_ptr;
        m_ptr = nullptr;
    }
}

template<typename B>
global<B>::~global()
{
    assert(m_ptr == nullptr && "Function destroy() was not called");
}

template<typename B>
B& global<B>::get()
{
    if(m_ptr == nullptr)
    {
        throw std::runtime_error(__PRETTY_FUNCTION__);
    }
    else
    {
        return *m_ptr;
    }
}

template<typename B>
bool global<B>::exists() const
{
    return m_ptr != nullptr;
}

class Matrix
{
public:
    Matrix() {}
    Matrix transpose() const { return Matrix{}; }
};

global<Matrix> gMatrix;

int main()
{
    // First, the global variable must be initialized
    assert(!gMatrix.exists());
    gMatrix.init(/* arguments to class Matrix*/);
    assert(gMatrix.exists());

    // Use the global variable of type Matrix
    gMatrix.get().transpose();

    // Lasst the global variable must be destroyed
    gMatrix.destroy();
    assert(!gMatrix.exists());
    return 0;
}
