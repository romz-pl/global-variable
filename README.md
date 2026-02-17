# Global variable


> [!NOTE]
> This is solid, production-quality C++20 code that demonstrates good understanding of modern C++ features for implementing **global variable**.
> 
> The main limitation is the locking strategy—holding a mutex during user callback execution limits throughput in concurrent scenarios. For many use cases, this is perfectly acceptable and provides strong safety guarantees.
