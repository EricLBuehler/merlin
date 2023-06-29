#include <memory>

// C++ Adaptation of my Rust implementation here: https://crates.io/crates/trc.
// It is not finished yet, but will be a thread-reference counted smart pointer with
// an atomic thread-shared reference count and a thread-local reference count for performance.
template<typename T> 
class Trc {
private:
    T* ptr;
public:
    Trc(T* data) {
        this->ptr = data;
    }
    Trc(T data) {
        this->ptr = new T(data);
    }

    ~Trc() {
        delete this->ptr;
    }

    T* operator->() {
        return this->ptr;
    }

    T operator*() {
        return *this->ptr;
    }

    size_t pointer_value() {
        return (size_t)this->ptr;
    }
};