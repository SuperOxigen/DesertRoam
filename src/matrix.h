#pragma once

#include <vector>
#include <stdexcept>

using std::vector;
using std::out_of_range;

// #define STORE_VECTOR

template <typename T>
class Matrix {

    // Y, X, (M, N)

    #ifdef STORE_VECTOR
    vector< vector<T> > values;
    #else
    T** values;
    #endif
    size_t _m, _n;

    void clearValues();

public:
    #ifdef STORE_VECTOR
    Matrix(size_t, size_t);
    Matrix(size_t);

    #else
    Matrix(size_t, size_t);
    Matrix(size_t);

    Matrix(Matrix const &);
    Matrix(Matrix&&);

    ~Matrix();
    Matrix& operator=(Matrix const &);

    #endif

    size_t getM() const { return _m; }
    size_t getN() const { return _n; }
    bool isSquare() const { return _m == _n; }

    bool inBound(int, int) const;
    T operator()(int, int) const;

    T& operator()(int, int);
    bool operator==(Matrix<T> const &) const;
    void fill(T);
    void reset(size_t = 0);
    void reset(size_t, size_t);
};

#ifdef STORE_VECTOR

template<typename T>
Matrix<T>::Matrix(size_t m, size_t n):
    values(vector< vector<T> >(m, vector<T>(n))), _m(m), _n(n) {}

template<typename T>
Matrix<T>::Matrix(size_t n):
    values(vector< vector<T> >(n, vector<T>(n))), _m(n), _n(n) {}

#else

template<typename T>
Matrix<T>::Matrix(size_t m, size_t n): 
    _m(m), _n(n)
{
    values = new T*[m];
    for (size_t i = 0; i < m; i++) values[i] = new T[n];
}

template<typename T>
Matrix<T>::Matrix(size_t n):
    _m(n), _n(n)
{
    values = new T*[n];
    for (size_t i = 0; i < n; i++) values[i] = new T[n];
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> const & other):
    _m(other._m), _n(other._n)
{
    values = new T*[_m];
    for (size_t i = 0; i < _m; i++)
    {
        values[i] = new T[_n];
        for (size_t j = 0; j < _n; j++)
            values[i][j] = other.values[i][j];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other):
    _m(other._m), _n(other._n)
{
    values = other.values;
    other.values = nullptr;
    other._m = 0;
    other._n = 0;
}

template<typename T>
Matrix<T>::~Matrix()
{
    clearValues();
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T> const & other)
{
    clearValues();

    _m = other._m;
    _n = other._n;

    values = new T*[_m];
    for (size_t i = 0; i < _m; i++)
    {
        values[i] = new T[_n];
        for (size_t j = 0; j < _n; j++)
            values[i][j] = other.values[i][j];
    }
}

#endif

template<typename T>
bool Matrix<T>::inBound(int y, int x) const
{
    return (y >= 0) && (y < _m) && (x >=0) && (x < _n);
}

template<typename T>
T Matrix<T>::operator()(int y, int x) const
{
    if (inBound(y,x))
    {
        return values[y][x];
    } 
    else
    {
        throw out_of_range("out of bounds");
    }   
}

#ifndef STORE_VECTOR

template<typename T>
void Matrix<T>::clearValues()
{
    if (values)
    {
        for (size_t i = 0; i < _m; i++)
        {
            if (_n != 0)
                delete[] values[i];
        }

        if (_m != 0)
            delete[] values;

        values = nullptr;
        _n = _m = 0;
    }
}

template<typename T>
T& Matrix<T>::operator()(int y, int x)
{
    if (inBound(y,x))
    {
        return values[y][x];
    }
    else
    {
        throw out_of_range("out of bounds");
    }
}

template<typename T>
bool Matrix<T>::operator==(Matrix<T> const & other) const
{
    if (_m != other._m || _n != other._n)
        return false;

    for (size_t i = 0; i < _m; i++)
    {
        for (size_t j = 0; j < _n; j++)
        {
            if (values[i][j] != other.values[i][j])
                return false;
        }
    }

    return true;
}

template<typename T>
void Matrix<T>::fill(T value)
{
    for (size_t i = 0; i < _m; i++)
    {
        for (size_t j = 0; j < _n; j++)
            values[i][j] = value;
    }
}

template<typename T>
void Matrix<T>::reset(size_t n)
{
    clearValues();
    _n = _m = n;
    values = new T*[n];
    for (size_t i = 0; i < n; i++) values[i] = new T[n];
}

template<typename T>
void Matrix<T>::reset(size_t m, size_t n)
{
    clearValues();
    _n = n;
    _m = m;
    values = new T*[m];
    for (size_t i = 0; i < m; i++) values[i] = new T[n];
}

#else

template<typename T>
void Matrix<T>::clearValues()
{
    values.clear();
    _n = _m = 0;    
}

template<typename T>
T& Matrix<T>::operator()(int y, int x)
{
    if (inBound(y,x))
    {
        return values[y][x];
    }
    else
    {
        throw out_of_range("out of bounds");
    }
}

template<typename T>
bool Matrix<T>::operator==(Matrix<T> const & other) const
{
    if (_m != other._m || _n != other._n)
        return false;

    for (size_t i = 0; i < _m; i++)
    {
        for (size_t j = 0; j < _n; j++)
        {
            if (values[i][j] != other.values[i][j])
                return false;
        }
    }

    return true;
}

template<typename T>
void Matrix<T>::fill(T value)
{
    for (auto itY = values.begin(); itY != values.end(); itY++)
    {
        for (auto itX = (*itY).begin(); itX != (*itY).end(); itX++)
        {
            *itX = value;
        }
    }
}

template<typename T>
void Matrix<T>::reset(size_t n)
{
    clearValues();
    _m = _n = n;
    values = vector< vector<T> >(n, vector<T>(n));
}

template<typename T>
void Matrix<T>::reset(size_t m, size_t n)
{
    clearValues();
    _n = n;
    _m = m;
    values = vector< vector<T> >(m, vector<T>(n));
}

#endif
