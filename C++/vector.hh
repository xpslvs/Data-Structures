/* vector.hh */
#ifndef VECTOR_HH
#define VECTOR_HH

#include <cmath>
#include <cstring>
#include <initializer_list>

template <int N, class T>
class Vector
{
public:
    Vector(void);
    Vector(const T *);
    Vector(const std::initializer_list<T>&);
    template <class U>
    operator Vector<N, U>(void) const;
    template <int M, class U>
    explicit operator Vector<M, U>(void) const;
    inline const T& operator[](int) const;
    inline       T& operator[](int);

    T      dot(const Vector&) const;
    Vector cross(const Vector&) const;
    T      quadrance(const Vector&) const;
    auto   distance(const Vector&) const;
    Vector proj(const Vector&) const;
    Vector perp(const Vector&) const;
    Vector normalize(void) const;
    T      norm(void) const;
    auto   magnitude(void) const;
    auto   angle(const Vector&) const;

    inline Vector operator +(void) const;
    inline Vector operator -(void) const;
    inline Vector operator +(const Vector&) const;
    inline Vector operator -(const Vector&) const;
    inline Vector operator *(const T&) const;
    inline Vector operator /(const T&) const;
    inline bool   operator ==(const Vector&) const;
    inline bool   operator !=(const Vector&) const;
    Vector operator +=(const Vector&);
    Vector operator -=(const Vector&);
    Vector operator *=(const T&);
    Vector operator /=(const T&);
private:
    T _element[N];
};

template <int N, class T>
Vector<N, T>::Vector(void)
{
    std::memset(this->_element, T(), N * sizeof(T));
}

template <int N, class T>
Vector<N, T>::Vector(const T *element)
{
    std::memcpy(this->_element, element, N * sizeof(T));
}

template <int N, class T>
Vector<N, T>::Vector(const std::initializer_list<T> &aggregate)
{
    auto iter = aggregate.begin();
    for(int i = 0; i < N; ++i)
    {
        this->_element[i] = (iter != aggregate.end()) ? *(iter++) : T();
    }
}

template <int N, class T>
template <class U>
Vector<N, T>::operator Vector<N, U>(void) const
{
    Vector<N, U> v{};
    for(int i = 0; i < N; ++i)
    {
        v[i] = static_cast<U>((*this)[i]);
    }
    return v;
}

template <int N, class T>
template <int M, class U>
Vector<N, T>::operator Vector<M, U>(void) const
{
    Vector<M, U> v{};
    for(int i = 0; i < N && i < M; ++i)
    {
        v[i] = static_cast<U>((*this)[i]);
    }
    return v;
}

template <int N, class T>
inline const T& Vector<N, T>::operator[](int index) const
{
    return this->_element[index];
}

template <int N, class T>
inline T& Vector<N, T>::operator[](int index)
{
    return this->_element[index];
}

template <int N, class T>
T Vector<N, T>::dot(const Vector<N, T>& v) const
{
    T p = T();
    for(int i = 0; i < N; ++i)
    {
        p += (*this)[i] * v[i];
    }
    return p;
}

 /* Defined only when N = 3
  */
template <int N, class T>
Vector<N, T> Vector<N, T>::cross(const Vector<N, T>& v) const
{
    Vector<3, T> u{};
    u[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
    u[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
    u[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
    return u;
}

template <int N, class T>
T Vector<N, T>::quadrance(const Vector<N, T>& v) const
{
    return ((*this) - v).norm();
}

template <int N, class T>
auto Vector<N, T>::distance(const Vector<N, T>& v) const
{
    return ((*this) - v).magnitude();
}

/* Project v onto this
 */
template <int N, class T>
Vector<N, T> Vector<N, T>::proj(const Vector<N, T>& v) const
{
    return ((*this) * (this->dot(v))) / this->norm();
}

template <int N, class T>
Vector<N, T> Vector<N, T>::perp(const Vector<N, T>& v) const
{
    return v - this->proj(v);
}

template <int N, class T>
Vector<N, T> Vector<N, T>::normalize(void) const
{
    return (*this) / this->magnitude();
}

template <int N, class T>
auto Vector<N, T>::angle(const Vector<N, T>& v) const
{
    return std::acos(this->dot(v) / (this->magnitude() * v.magnitude()));
}

template <int N, class T>
T Vector<N, T>::norm(void) const
{
    return this->dot(*this);
}

template <int N, class T>
auto Vector<N, T>::magnitude(void) const
{
    return std::sqrt(this->norm());
}

template <int N, class T>
inline Vector<N, T> Vector<N, T>::operator +(void) const
{
    return (*this);
}

template <int N, class T>
inline Vector<N, T> Vector<N, T>::operator -(void) const
{
    return (*this) * (-1);
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator +(const Vector<N, T>& v) const
{
    return Vector<N, T>(*this) += v;
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator -(const Vector<N, T>& v) const
{
    return Vector<N, T>(*this) -= v;
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator *(const T& c) const
{
    return Vector<N, T>(*this) *= c;
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator /(const T& c) const
{
    return Vector<N, T>(*this) /= c;
}

template <int N, class T>
inline bool Vector<N, T>::operator ==(const Vector<N, T>& v) const
{
    return std::memcmp(this->_element, v._element, N * sizeof(T)) == 0;
}

template <int N, class T>
inline bool Vector<N, T>::operator !=(const Vector<N, T>& v) const
{
    return std::memcmp(this->_element, v._element, N * sizeof(T)) != 0;
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator +=(const Vector<N, T>& v) 
{
    for(int i = 0; i < N; ++i)
    {
        (*this)[i] += v[i];
    }
    return (*this);
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator -=(const Vector<N, T>& v)
{
    for(int i = 0; i < N; ++i)
    {
        (*this)[i] -= v[i];
    }
    return (*this);
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator *=(const T& c)
{
    for(int i = 0; i < N; ++i)
    {
        (*this)[i] *= c;
    }
    return (*this);
}

template <int N, class T>
Vector<N, T> Vector<N, T>::operator /=(const T& c)
{
    for(int i = 0; i < N; ++i)
    {
        (*this)[i] /= c;
    }
    return (*this);
}

typedef Vector<2, unsigned> Vector2u;
typedef Vector<3, unsigned> Vector3u;
typedef Vector<4, unsigned> Vector4u;
typedef Vector<2, int>      Vector2i;
typedef Vector<3, int>      Vector3i;
typedef Vector<4, int>      Vector4i;
typedef Vector<2, float>    Vector2f;
typedef Vector<3, float>    Vector3f;
typedef Vector<4, float>    Vector4f;
typedef Vector<2, double>   Vector2lf;
typedef Vector<3, double>   Vector3lf;
typedef Vector<4, double>   Vector4lf;

#endif
