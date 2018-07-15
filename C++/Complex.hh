/* Complex.hh */
#ifndef COMPLEX_HH
#define COMPLEX_HH

#include <cmath>

template <class T>
class Complex
{
public:
    Complex(const T& = T(), const T& = T());
    template <class U>
    operator Complex<U>(void) const;
    explicit operator T(void) const;
    inline void set(const T&, const T&);
    inline const T& real(void) const;
    inline const T& imag(void) const;
    inline T& real(void);
    inline T& imag(void);

    Complex reciprocal(void) const;
    Complex conjugate(void) const;
    Complex square(void) const;
    Complex pow(const Complex&) const;
    Complex pow(const T&) const;
    Complex sqrt(void) const;
    Complex exp(void) const;
    Complex log(void) const;
    T       norm(void) const;
    auto    modulus(void) const;
    auto    argument(void) const;

    inline Complex operator +(void) const;
    inline Complex operator -(void) const;
    inline Complex operator +(const Complex&) const;
    inline Complex operator -(const Complex&) const;
    inline Complex operator *(const Complex&) const;
    inline Complex operator *(const T&) const;
    inline Complex operator /(const Complex&) const;
    inline Complex operator /(const T&) const;
    inline bool operator ==(const Complex&) const;
    inline bool operator !=(const Complex&) const;
    Complex operator +=(const Complex&);
    Complex operator -=(const Complex&);
    Complex operator *=(const Complex&);
    Complex operator *=(const T&);
    Complex operator /=(const Complex&);
    Complex operator /=(const T&);
 private:
    T _real;
    T _imag;
};

template <class T>
Complex<T>::Complex(const T& real, const T& imag)
{
    this->set(real, imag);
}

template <class T>
inline void Complex<T>::set(const T& real, const T& imag)
{
    this->_real = real;
    this->_imag = imag;
}

template <class T>
template <class U>
Complex<T>::operator Complex<U>(void) const
{
    return {static_cast<U>(this->real()), static_cast<U>(this->imag())};
}

template <class T>
Complex<T>::operator T(void) const
{
    return this->real();
}


template <class T>
inline const T& Complex<T>::real(void) const
{
    return this->_real;
}

template <class T>
inline const T& Complex<T>::imag(void) const
{
    return this->_imag;
}

template <class T>
inline T& Complex<T>::real(void)
{
    return this->_real;
}

template <class T>
inline T& Complex<T>::imag(void)
{
    return this->_imag;
}

template <class T>
Complex<T> Complex<T>::reciprocal(void) const
{
    return this->conjugate() / this->norm();
}

template <class T>
Complex<T> Complex<T>::conjugate(void) const
{
    return {this->real(), -this->imag()};
}


template <class T>
Complex<T> Complex<T>::square(void) const
{
    Complex<T> z{};
    z.real()  = this->real() * this->real() - this->imag() * this->imag();
    z.imag()  = this->real() * this->imag() * 2;
    return z;
}

template <class T>
Complex<T> Complex<T>::pow(const Complex<T>& z) const
{
    Complex<T> w{};
    const T phi = z.imag() * std::log(this->modulus()) + z.real() * this->argument();
    const T mod = std::exp(z.real() * std::log(this->modulus()) - z.imag() * this->argument());
    w.set(std::cos(phi), std::sin(phi));
    return w * mod;
}

template <class T>
Complex<T> Complex<T>::pow(const T& c) const
{
    Complex<T> z{};
    z.real() = std::cos(this->argument() * c);
    z.imag() = std::sin(this->argument() * c);
    return z * std::pow(this->norm(), c / 2);
}

template <class T>
Complex<T> Complex<T>::sqrt(void) const
{
    Complex z{};
    z.real() = std::cos(this->argument() / 2);
    z.imag() = std::sin(this->argument() / 2);
    return z * std::sqrt(this->modulus());
}

template <class T>
Complex<T> Complex<T>::exp(void) const
{
    Complex<T> z{};
    z.real() = std::cos(this->imag());
    z.imag() = std::sin(this->imag());
    return z * std::exp(this->real());
}

template <class T>
Complex<T> Complex<T>::log(void) const
{
    return {std::log(this->modulus()), this->argument()};
}

template <class T>
T Complex<T>::norm(void) const
{
    return this->real() * this->real() + this->imag() * this->imag();
}

template <class T>
auto Complex<T>::modulus(void) const
{
    return std::sqrt(this->norm());
}


template <class T>
auto Complex<T>::argument(void) const
{
    return std::atan(this->imag() / this->real());
}

template <class T>
inline Complex<T> Complex<T>::operator +(void) const
{
    return (*this);
}

template <class T>
inline Complex<T> Complex<T>::operator -(void) const
{
    return {-this->real(), -this->imag()};
}

template <class T>
inline Complex<T> Complex<T>::operator +(const Complex<T> &z) const
{
    return Complex<T>(*this) += z;
}

template <class T>
inline Complex<T> Complex<T>::operator -(const Complex<T> &z) const
{
    return Complex<T>(*this) -= z;
}

template <class T>
inline Complex<T> Complex<T>::operator *(const Complex<T> &z) const
{
    return Complex<T>(*this) * z;
}

template <class T>
inline Complex<T> Complex<T>::operator *(const T &c) const
{
    return Complex<T>(*this) * c;
}

template <class T>
inline Complex<T> Complex<T>::operator /(const Complex<T> &z) const
{
    return Complex<T>(*this) / z;
}

template <class T>
inline Complex<T> Complex<T>::operator /(const T &c) const
{
    return Complex<T>(*this) / c;
}
template <class T>
inline bool Complex<T>::operator ==(const Complex<T> &z) const
{
    return this->real() == z.real() && this->imag() == z.imag();
}

template <class T>
inline bool Complex<T>::operator !=(const Complex<T> &z) const
{
    return this->real() != z.real() || this->imag() != z.imag();
}

template <class T>
Complex<T> Complex<T>::operator +=(const Complex<T> &z)
{
    this->real() += z.real();
    this->imag() += z.imag();
    return (*this);
}

template <class T>
Complex<T> Complex<T>::operator -=(const Complex<T> &z)
{
    this->real() -= z.real();
    this->imag() -= z.imag();
    return (*this);
}

template <class T>
Complex<T> Complex<T>::operator *=(const Complex &z)
{
    this->set(
        this->real() * z.real() - this->imag() * z.imag(),
        this->real() * z.imag() + this->imag() * z.real()
    );
    return (*this);

}

template <class T>
Complex<T> Complex<T>::operator *=(const T &c)
{
    this->real() *= c;
    this->imag() *= c;
    return (*this);
}

template <class T>
Complex<T> Complex<T>::operator /=(const Complex &z)
{
    this->set(
        this->real() * z.real() + this->imag() * z.imag(),
        this->imag() * z.real() - this->real() * z.imag()
    );
    (*this) /= z.norm();
    return (*this);
}

template <class T>
Complex<T> Complex<T>::operator /=(const T &c)
{
    this->real() /= c;
    this->imag() /= c;
    return (*this);
}

typedef Complex<float>       Complexf;
typedef Complex<double>      Complexlf;
typedef Complex<long double> ComplexLf;

#endif
