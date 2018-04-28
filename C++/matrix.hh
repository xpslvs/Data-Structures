/* matrix.hh */
#ifndef MATRIX_HH
#define MATRIX_HH

#include <cmath>
#include <cstring>
#include <initializer_list>
#include "vector.hh"

/* Rows, Columns, Scalar type
 * Uses row-column notation
 */
template <unsigned R, unsigned C, typename T>
class Matrix
{
public:
	Matrix(void)
	{
		std::memset(this->_elem, (T)0, R * C * sizeof(T));
	}

	Matrix(const T matrix[R][C])
	{
		std::memcpy(this->_elem, matrix, R * C * sizeof(T));
	}

	Matrix(const Vector<R, T> &v)
	{
		static_assert(C == 1, "Vector cannot be casted to a matrix of width larger than 1");
		
		for(unsigned i = 0; i < R; ++i)
		{
			(*this)[i][0] = v.elem(i);
		}
	}

	Matrix(const std::initializer_list<Vector<R, T>> &aggregate)
	{
		auto iter = aggregate.begin();
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				(*this)[i][j] = (*iter).elem(j);
			}
			if(++iter == aggregate.end())
				return;
		}
	}
	
	/* Assumes there are atleast C elements in the array
	 */
	Matrix(const Vector<R, T> vectors[C])
	{
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				this->_elem[i][j] = vectors[j][i];
			}
		}
	}

	Matrix add(const Matrix &a)
	{
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				(*this)[i][j] += a.elem(i, j);
			}
		}
		return (*this);
	}

	Matrix subtract(const Matrix &a)
	{
		return this->add(-a);
	}

	Matrix multiply(const T &c)
	{
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				(*this)[i][j] *= c;
			}
		}
		return (*this);
	}

	Matrix divide(const T &c)
	{
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				(*this)[i][j] /= c;
			}
		}
		return (*this);
	}
	
	template <unsigned N, unsigned M>
	Matrix<R, M, T> multiply(const Matrix<N, M, T> &a) const
	{
		static_assert(C == N, "Multiplication between RxC and NxM matrices is only defined for C == N");

		Matrix<R, M, T> b{};
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < M; ++j)
			{
				for(unsigned k = 0; k < C; ++k)
				{
					b[i][j] += this->elem(i, k) * a.elem(k, j);
				}
			}
		}
		return b;
	}

	Matrix<C, R, T> transpose(void) const
	{
		Matrix<C, R, T> a{};
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				a[j][i] = this->elem(i, j);
			}
		}
		return a;
	}

	T determinant(void) const
	{
		static_assert(C == R, "Determinant is only defined for square matrices");

		return Matrix::determinant(*this);
	}

	
	Matrix reciprocal(void) const
	{
		static_assert(C == R, "Reciprocal is only defined for square matrices");

		return (*this); // Not implemented
	}

	bool equals(const Matrix &a) const
	{
		return !std::memcmp(this->_elem, a._elem, R * C * sizeof(T));
	}

	/* No bounds checking is done on the element accessor functions
	 */
	inline T elem(unsigned i, unsigned j) const
	{
		return this->_elem[i][j];
	}

	inline T *operator [](unsigned i)
	{
		return this->_elem[i];
	}

	/* Casting to different type is done implicitly
	 */
	template <typename S>
	operator Matrix<R, C, S>(void) const
	{
		Matrix<R, C, S> a{};
		for(unsigned i = 0; i < R; ++i)
		{
			for(unsigned j = 0; j < C; ++j)
			{
				a[i][j] = (S)this->elem(i, j);
			}
		}
		return a;
	}

	template<unsigned N>
	operator Vector<N, T>(void) const
	{
		static_assert(R == 1 || C == 1, "Matrix width or height needs to be equal to 1 to enable casting to vector");

		if constexpr(R == 1)
			return (Vector<N, T>)(this->_elem[0]);
		else
			return (Vector<N, T>)(this->transpose()._elem[0]);
	}

	inline Matrix operator +(void) const
	{
		return (*this);
	}

	inline Matrix operator -(void) const
	{
		return (*this) * (-1);
	}

	inline Matrix operator +(const Matrix &a) const
	{
		return ((Matrix)(*this)).add(a);
	}

	inline Matrix operator -(const Matrix &a) const
	{
		return ((Matrix)(*this)).subtract(a);
	}

	inline Matrix operator *(const T &c) const
	{
		return ((Matrix)(*this)).multiply(c);
	}

	inline Matrix operator /(const T &c) const
	{
		return ((Matrix)(*this)).divide(c);
	}

	template <unsigned N, unsigned M>
	Matrix<R, M, T> operator *(const Matrix<N, M, T> &a) const
	{
		return ((Matrix)(*this)).multiply(a);
	}

	template <unsigned N>
	Matrix<N, 1, T> operator *(const Vector<N, T> &v)
	{
		return ((Matrix)(*this)).multiply((Matrix<N, 1, T>)v);
	}

	template <unsigned N>
	inline Matrix operator ~(void) const
	{
		return this->reciprocal();
	}

	inline bool operator ==(const Matrix &a) const
	{
		return this->equals(a);
	}

	inline bool operator !=(const Matrix &a) const
	{
		return !this->equals(a);
	}

	inline Matrix operator +=(const Matrix &a) 
	{
		return this->add(a);
	}

	inline Matrix operator -=(const Matrix &a) 
	{
		return this->subtract(a);
	}

	inline Matrix operator *=(const T &c)
	{
		return this->multiply(c);
	}

	template <unsigned N>
	inline Matrix<N, N, T> operator *=(const Matrix<N, N, T> &a)
	{
		return (*this) = this->multiply(a);
	}

	inline Matrix operator /=(T const &c)
	{
		return this->divide(c);
	}
private:
	T _elem[R][C];

	static T determinant(const Matrix<2, 2, T> &a)
	{
		return (a.elem(0, 0)*a.elem(1, 1)) - (a.elem(1, 0)*a.elem(0, 1));
	}

	static T determinant(const Matrix<3, 3, T> &a)
	{
		T det = 0;
		det += a.elem(0,0) * ((a.elem(1,1)*a.elem(2,2)) - (a.elem(1,2)*a.elem(2,1)));
		det -= a.elem(0,1) * ((a.elem(1,0)*a.elem(2,2)) - (a.elem(1,2)*a.elem(2,0)));
		det += a.elem(0,2) * ((a.elem(1,0)*a.elem(2,1)) - (a.elem(1,1)*a.elem(2,0)));
		return det;
	}

	template <unsigned N>
	static T determinant(const Matrix<N, N, T> &a)
	{
		return (T)0; // Not implemented 
	}
};

typedef Matrix<2, 2, unsigned> Matrix2u;
typedef Matrix<3, 3, unsigned> Matrix3u;
typedef Matrix<4, 4, unsigned> Matrix4u;
typedef Matrix<2, 2, int>      Matrix2i;
typedef Matrix<3, 3, int>      Matrix3i;
typedef Matrix<4, 4, int>      Matrix4i;
typedef Matrix<2, 2, float>    Matrix2f;
typedef Matrix<3, 3, float>    Matrix3f;
typedef Matrix<4, 4, float>    Matrix4f;
typedef Matrix<2, 2, double>   Matrix2lf;
typedef Matrix<3, 3, double>   Matrix3lf;
typedef Matrix<4, 4, double>   Matrix4lf;

#endif /* MATRIX_HH */
