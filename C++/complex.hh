/* complex.hh */
#ifndef COMPLEX_HH
#define COMPLEX_HH

#include <cmath>

/* An implementation of complex numbers with support for 
 * complex exponents, along with some fast implementations
 * for a few specific functions
 * Defines typedefs for float, double and long double
 * Uses operator overloads for the most common arithmetic functions
 * Depends on <cmath> header
 */
template <typename T>
class Complex
{
public:
	Complex(const T &real = 0, const T &imag = 0)
	{
		this->set(real, imag);
	}

	Complex add(const Complex &z) const
	{
		Complex w{*this};
		w._real += z.real();
		w._imag += z.imag();
		return w;
	}

	Complex subtract(const Complex &z) const
	{
		Complex w{*this};
		w._real -= z.real();
		w._imag -= z.imag();
		return w;
	}

	Complex multiply(const Complex &z) const
	{
		Complex w{};
		w._real = (this->real() * z.real()) - (this->imag() * z.imag());
		w._imag = (this->imag() * z.real()) + (this->real() * z.imag());
		return w;
	}

	Complex multiply(const T &c) const
	{
		Complex z{*this};
		z._real *= c;
		z._imag *= c;
		return z;
	}

	Complex divide(const Complex &z) const
	{
		Complex w{};
		w._real = this->real() * z.real() + this->imag() * z.imag();
		w._imag = this->imag() * z.real() - this->real() * z.imag();
		w._real /= z.norm();
		w._imag /= z.norm();
		return w;
	}
	
	Complex divide(const T &c) const
	{
		Complex z{*this};
		z._real /= c;
		z._imag /= c;
		return z;
	}
	
	Complex square(void) const
	{
		Complex z{};
		z._real  = this->real() * this->real();
		z._real -= this->imag() * this->imag();
		z._imag  = this->real() * this->imag() * 2;
		return z;
	}

    Complex pow(const Complex &z) const
    {
        Complex w{};
        w._real = std::cos(z.imag() * std::log(this->modulus()) + z.real() * this->argument());
        w._imag = std::sin(z.imag() * std::log(this->modulus()) + z.real() * this->argument());
        w *= std::exp(z.real() * std::log(this->modulus()) - z.imag() * this->argument());
        return w;
    }

    Complex pow(const T &c) const
	{
		Complex z{};
		z._real = std::cos(this->argument() * c);
		z._imag = std::sin(this->argument() * c);
		z *= (T)std::pow(this->norm(), c / 2);
		return z;
	}

    Complex exp(void) const
    {
        Complex z{};
        z._real = std::cos(this->imag());
        z._imag = std::sin(this->imag());
        z *= std::exp(this->real());
        return z;
    }

    Complex sqrt(void) const
    {
        Complex z{};
        z._real = std::cos(this->argument() / 2);
        z._imag = std::sin(this->argument() / 2);
        z *= (T)std::sqrt(this->modulus());
        return z;
    }

	Complex reciprocal(void) const
	{
		Complex z{this->conjugate()};
		z._real /= this->norm();
		z._imag /= this->norm();
		return z;
	}

	Complex conjugate(void) const
	{
		return {this->real(), -this->imag()};
	}

	T argument(void) const
	{
		return std::atan(this->imag() / this->real());
	}

	/* Evaluates to the magnitude/modulus squared
	 */
	T norm(void) const
	{
		return this->real() * this->real() + this->imag() * this->imag();
	}

	T modulus(void) const
	{
		return (T)std::sqrt(this->norm());
	}

	bool equals(const Complex &z) const
	{
		return this->real() == z.real() && this->imag() == z.imag();
	}

	void set(const T &real, const T &imag)
	{
		this->_real = real;
		this->_imag = imag;
	}

	/* Casting to other types of complex numbers
	 * is done implicitly
	 */
	template <typename S>
	operator Complex<S>(void) const
	{
		return {(S)this->real(), (S)this->imag()};
	}
	
	/* Casting to real part is done explicitly through casting
	 */
	template <typename S>
	explicit operator S(void) const
	{
		return (S)this->real();
	}

	inline T real(void) const
	{
		return this->_real;
	}

	inline T imag(void) const
	{
		return this->_imag;
	}

	inline Complex operator +(void) const
	{
		return (*this);
	}

	inline Complex operator -(void) const
	{
		return {-this->real(), -this->imag()};
	}

	inline Complex operator +(const Complex &z) const
	{
		return this->add(z);
	}

	inline Complex operator -(const Complex &z) const
	{
		return this->subtract(z);
	}

	inline Complex operator *(const Complex &z) const
	{
		return this->multiply(z);
	}

	inline Complex operator *(const T &c) const
	{
		return this->multiply(c);
	}

	inline Complex operator /(const Complex &z) const
	{
		return this->divide(z);
	}

	inline Complex operator /(const T &c) const
	{
		return this->divide(c);
	}

	inline Complex operator +=(const Complex &z)
	{
		return (*this) = (*this) + z;
	}

	inline Complex operator -=(const Complex &z)
	{
		return (*this) = (*this) - z;
	}

	inline Complex operator *=(const Complex &z)
	{
		return (*this) = (*this) * z;
	}

	inline Complex operator *=(const T &c)
	{
		return (*this) = (*this) * c;
	}

	inline Complex operator /=(const Complex &z)
	{
		return (*this) = (*this) / z;
	}

	inline Complex operator /=(const T &c)
	{
		return (*this) = (*this) / c;
	}

	inline bool operator ==(const Complex &z) const
	{
		return this->equals(z);
	}

	inline bool operator !=(const Complex &z) const
	{
		return !this->equals(z);
	}

	inline bool operator >=(const Complex &z) const
	{
		return this->norm() >= z.norm();
	}

	inline bool operator <=(const Complex &z) const
	{
		return this->norm() <= z.norm();
	}

	inline bool operator >(const Complex &z) const
	{
		return this->norm() > z.norm();
	}

	inline bool operator <(const Complex &z) const
	{
		return this->norm() < z.norm();
	}
private:
	T _real;
	T _imag;
};

typedef Complex<float>       Complexf;
typedef Complex<double>      Complexlf;
typedef Complex<long double> ComplexLf;

#endif /* COMPLEX_HH */
