/* vector.hh */
#ifndef VECTOR_HH
#define VECTOR_HH

#include <cmath>
#include <cstring>
#include <initializer_list>

/* # Elements, 
 * Scalar type
 */
template <unsigned N, typename T>
class Vector
{
public:
	Vector(void)
	{
		std::memset(this->_elem, 0, N * sizeof(T));
	}

	Vector(const T v[N])
	{
		std::memcpy(this->_elem, v, N * sizeof(T));
	}

	Vector(const std::initializer_list<T> &aggregate)
	{
		auto iter = aggregate.begin();
		for(unsigned i = 0; i < N; ++i)
		{
			this->_elem[i] = iter != aggregate.end() ? *iter++ : (T)0;
		}
	}

	Vector add(const Vector &v)
	{
		for(unsigned i = 0; i < N; ++i)
		{
			(*this)[i] += v.elem(i);
		}
		return *this;
	}
	
	Vector subtract(const Vector &v)
	{
		return this->add(-v);
	}
	
	/* Scalar multiplication
	 */
	Vector multiply(const T &c)
	{
		for(unsigned i = 0; i < N; ++i)
		{
			(*this)[i] *= c;
		}
		return *this;
	}

	Vector divide(const T &c)
	{
		for(unsigned i = 0; i < N; ++i)
		{
			(*this)[i] /= c;
		}
		return *this;
	}

	/* Scalar/dot product
	 */
	T dot(const Vector &v) const
	{
		T p = (T)0;
		for(unsigned i = 0; i < N; ++i)
		{
			p += this->elem(i) * v.elem(i);
		}
		return p;
	}
	
	Vector<3, T> cross(const Vector<3, T> &v) const
	{
		static_assert(N == 3, "Cross product is only defined for vectors of size 3");

		Vector<3, T> u{};
		u[0] = this->elem(1) * v.elem(2) - this->elem(2) * v.elem(1);
		u[1] = this->elem(2) * v.elem(0) - this->elem(0) * v.elem(2);
		u[2] = this->elem(0) * v.elem(1) - this->elem(1) * v.elem(0);
		return u;
	}

	/* Project vector v onto this
	 */
	Vector project(const Vector &v) const
	{
		return (*this) * (this->dot(v) / this->norm());
	}
	
	Vector normalize(void) const
	{
		return (*this) / this->magnitude();
	}

	T angle(const Vector &v) const
	{
		return (T)std::acos(this->dot(v) / (this->magnitude() * v.magnitude()));
	}

	bool equals(const Vector &v) const
	{
		return !std::memcmp(this->_elem, v._elem, N * sizeof(T));
	}
	
	T magnitude(void) const
	{
		return (T)std::sqrt(this->norm());
	}
	
	/* Magnitude squared
	 */
	T norm(void) const
	{
		return this->dot(*this);
	}

	/* Casting to a different size can be done explicitly 
	 */
	template <unsigned M>
	explicit operator Vector<M, T>(void) const
	{
		Vector<M, T> v{};
		for(unsigned i = 0; i < (M < N ? M : N); ++i)
		{
			v[i] = this->elem(i);
		}
		return v;
	}

	template <unsigned M, typename S>
	explicit operator Vector<M, S>(void) const
	{
		return (Vector<M, S>)((Vector<M, T>)(*this));
	}

	/* Casting to a different scalar type can be done implicitly
	 */
	template <typename S>
	operator Vector<N, S>(void) const
	{
		Vector<N, S> v;
		for(unsigned i = 0; i < N; ++i)
		{
			v[i] = (S)this->elem(i);
		}
		return v;
	}

	/* No index checking is done when using element accessors
	 */
	inline T elem(unsigned i) const
	{
		return this->_elem[i];
	}

	inline T& operator [](unsigned i)
	{
		return this->_elem[i];
	}

	inline T x(void) const
	{
		return this->elem(0); 
	}

	inline T y(void) const
	{
		return this->elem(1); 
	}

	inline T z(void) const
	{
		return this->elem(2);
	}

	inline T w(void) const
	{
		return this->elem(3);
	}

	inline Vector operator +(void) const
	{
		return (*this);
	}
	
	inline Vector operator -(void) const
	{
		return (*this) * (-1);
	}
	
	inline Vector operator +(const Vector &v) const 
	{
		return ((Vector)(*this)).add(v);
	}
	
	inline Vector operator -(const Vector &v) const
	{
		return ((Vector)(*this)).subtract(v);
	}
	
	inline Vector operator *(const T &c) const
	{
		return ((Vector)(*this)).multiply(c);
	}

	inline Vector operator /(const T &c) const
	{
		return ((Vector)(*this)).divide(c);
	}
	
	inline bool operator ==(const Vector &v) const
	{
		return this->equals(v);
	}

	inline bool operator !=(const Vector &v) const
	{
		return !this->equals(v);
	}
	
	inline Vector operator +=(const Vector &v)
	{
		return this->add(v);
	}
	
	inline Vector operator -=(const Vector &v)
	{
		return this->subtract(v);
	}
	
	inline Vector operator *=(const T &c)
	{
		return this->multiply(c);
	}

	inline Vector operator /=(const T &c)
	{
		return this->divide(c);
	}
private:
	T _elem[N];
};

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

#endif /* VECTOR_HH */
