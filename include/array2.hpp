#ifndef RL_UTILS_ARRAY2_HPP
#define RL_UTILS_ARRAY2_HPP

#include <functional>

#include "pos.hpp"

// Two dimensional array class
template<typename T>
class Array2
{
public:
    Array2() :
        data_   (nullptr),
        dims_   (0, 0) {}

    Array2(const P& dims) :
        data_   (nullptr),
        dims_   ()
    {
        resize(dims);
    }

    Array2(const int w, const int h) :
        data_   (nullptr),
        dims_   ()
    {
        resize(P(w, h));
    }

    ~Array2()
    {
        delete[] data_;
    }

    Array2& operator=(const Array2& other)
    {
        delete[] data_;

        data_ = other.data_;
        dims_ = other.dims_;

        return *this;
    }

    void resize(const P& dims)
    {
        dims_ = dims;

        const size_t size = nr_elements();

        delete[] data_;

        data_ = new T[size];
    }

    void resize(const int w, const int h)
    {
        resize(P(w, h));
    }

    T& operator()(const P& p)
    {
        check_pos(p);

        const size_t idx = pos_to_idx(p);

        return data_[idx];
    }

    const T& operator()(const P& p) const
    {
        return (*const_cast<Array2*>(this))(p);
    }

    T& operator()(const int x, const int y)
    {
        return (*this)(P(x, y));
    }

    const T& operator()(const int x, const int y) const
    {
        return (*this)(P(x, y));
    }

    void for_each(std::function<void(T& v)> func)
    {
        const size_t size = nr_elements();

        for (size_t idx = 0; idx < size; ++idx)
        {
            func(data_[idx]);
        }
    }

    void clear()
    {
        delete[] data_;

        dims_.set(0, 0);
    }

    const P& dims() const
    {
        return dims_;
    }

private:
    size_t pos_to_idx(const P& p) const
    {
        return (p.x * dims_.y) + p.y;
    }

    size_t nr_elements() const
    {
        return dims_.x * dims_.y;
    }

    void check_pos(const P& p) const
    {
        if (p.x >= dims_.x || p.y >= dims_.y)
        {
            ASSERT(false);
        }
    }

    T* data_;
    P dims_;
};

#endif // RL_UTILS_ARRAY2_HPP
