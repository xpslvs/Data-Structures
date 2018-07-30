/* Stack.hh */
#ifndef STACK_HH
#define STACK_HH

#include <cstddef>
#include <cstring>
#include <exception>
#include <stdexcept>

template <typename T>
class Stack
{
public:
	Stack(size_t size = 0)
	{
		this->_base     = nullptr;
		this->_pointer  = nullptr;
		this->_capacity = 0;
		this->allocate(size);
	}
	
	Stack(const Stack &stack)
	{
		(*this) = stack;
	}

	void operator =(const Stack &stack)
	{
		if(this->_base != nullptr)
			delete[] this->_base;
		Stack copy      = stack.copy();
		this->_base     = copy._base;
		this->_pointer  = copy._pointer;
		this->_capacity = copy._capacity;
	}

	~Stack(void)
	{
		delete[] this->_base;
	}

	/* Constructs a new stack with identical capacity and data
	 */
	Stack copy(void) const
	{
		Stack stack(this->capacity());
		std::memcpy(stack._base, this->_base, this->capacity() * sizeof(T));
		stack._pointer += this->size();
		return stack;
	}
	
	/* Allocates size * sizeof(T) bytes to the stack
	 * If memory already allocated, the old data is copied to the resized stack
	 * If the new size is smaller than the already allocated size, the data is copied
	 * from the bottom of the stack up to the new size
	 */
	void allocate(size_t size)
	{
		T *memory     = new T[size];
		size_t offset = this->size();

		if(this->_base != nullptr)
		{
			std::memcpy(
				memory, 
				this->_base, 
				(this->_capacity > size ? size : this->_capacity) * sizeof(T)
			);
			delete[] this->_base;
		}

		this->_base     = memory;
		this->_pointer  = this->_base + offset;
		this->_capacity = size;
	}
	
	void clear(void)
	{
		this->_pointer = this->_base;
	}

	size_t size(void) const
	{
		return (size_t)(this->_pointer - this->_base);
	}
	
	size_t capacity(void) const
	{
		return this->_capacity;
	}

	void push(const T &x)
	{
		if(this->size() >= this->capacity())
			throw std::overflow_error("Stack overflow");
		*(this->_pointer++) = x;
	}
	
	T pop(void)
	{
		if(this->size() <= 0)
			throw std::underflow_error("Stack underflow");
		return *(--this->_pointer);
	}
	
	void pick(size_t n)
	{
		if(this->size() <= n)
			throw std::underflow_error("Stack underflow");
		this->push(this->_pointer[-(int)(n+1)]);
	} 

	void roll(size_t n)
	{
		this->pick(n);
		for(long long i = -(long long)(n+2); i <= -2; ++i)
		{
			this->_pointer[i] = this->_pointer[i+1];
		}
		this->drop();
	}
	
	inline T peek(void)
	{
		const T x = this->pop();
		this->push(x);
		return x;
	}
	
	/* ( n1 n2 -- n1 n2 n2 )
	 */
	inline void dup(void)
	{
		this->pick(0);
	}
	
	/* ( n1 n2 -- n1 )
	 */
	inline void drop(void)
	{
		this->pop();
	}

	/* ( n1 n2 n3 -- n1 n3 n2 )
	 */
	inline void swap(void)
	{
		this->roll(1);
	}

	/* ( n1 n2 -- n1 n2 n1 )
	 */
	inline void over(void)
	{
		this->pick(1);
	}

	/* ( n1 n2 n3 -- n2 n3 n1 )
	 */
	inline void rot(void)
	{
		this->roll(2);
	}

	/* ( n1 n2 n3 -- n1 n3 )
	 */
	inline void nip(void) 
	{
		this->swap();
		this->drop();
	}
	
	/* ( n1 n2 n3 -- n1 n3 n2 n3 )
	 */
	inline void tuck(void)
	{
		this->swap();
		this->over();
	}
private:
	T *_base;
	T *_pointer;
	size_t _capacity;
};

#endif
