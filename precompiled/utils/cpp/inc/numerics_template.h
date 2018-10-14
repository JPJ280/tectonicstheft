#pragma once

#include "primitives_template.h"

namespace rasters
{

	// This template represents a statically-sized contiguous block of memory occupied by numeric data of arbitrary type
	// The intention is to abstract away numeric arrays that are used to address data locality issues
	// the numeric data type should be small enough to fit in a computer's register (e.g. ints, floats, and even vec3s)
	// the numeric data type must have all the standard arithmetic operators as regular ints/floats: + - * / < > <= >= == != 
	// the arithmetic operators must share the same general behavior as ints/floats (i.e. no dot products or element-wise comparators)
	template <class T>
	class numerics_template : public primitives_template<T>
	{

	public:

		numerics_template(const unsigned int N) : primitives_template<T>(N) {};

		numerics_template(const unsigned int N, const T a)  : primitives_template<T>(N, a) {};

		numerics_template(const numerics_template<T>& a)  : primitives_template<T>(a) {};

		static T min(const numerics_template<T>& a)
		{
			T out = a.values[0];
			for (int i = 0; i < a.N; ++i)
			{
				out = a.values[i] < out? a.values[i] : out;
			}
			return out;
		}
		static T max(const numerics_template<T>& a)
		{
			T out = a.values[0];
			for (int i = 0; i < a.N; ++i)
			{
				out = a.values[i] > out? a.values[i] : out;
			}
			return out;
		}




		template <class T2>
		static void gt(const numerics_template<T>& a, const T2 b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] > b;
			}
		}
		template <class T2>
		static void gte(const numerics_template<T>& a, const T b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] >= b;
			}
		}
		template <class T2>
		static void lt(const numerics_template<T>& a, const T2 b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] < b;
			}
		}
		template <class T2>
		static void lte(const numerics_template<T>& a, const T2 b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] <= b;
			}
		}





		template <class T2>
		static void gt(const numerics_template<T>& a, const numerics_template<T2>& b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] > b.values[i];
			}
		}
		template <class T2>
		static void gte(const numerics_template<T>& a, const numerics_template<T2>& b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] >= b.values[i];
			}
		}
		template <class T2>
		static void lt(const numerics_template<T>& a, const numerics_template<T2>& b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] <= b.values[i];
			}
		}
		template <class T2>
		static void lte(const numerics_template<T>& a, const numerics_template<T2>& b, bools& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] < b.values[i];
			}
		}





		template <class T2, class T3>
		static void add(const numerics_template<T>& a, const T2 b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] + b;
			}
		}
		template <class T2, class T3>
		static void sub(const numerics_template<T>& a, const T2 b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] - b;
			}
		}
		template <class T2, class T3>
		static void mult(const numerics_template<T>& a, const T2 b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] * b;
			}
		}
		template <class T2, class T3>
		static void div(const numerics_template<T>& a, const T2 b, numerics_template<T3>& out)
		{
			const T ainv = 1./b;
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] / b;
			}
		}



		template <class T2, class T3>
		static void add(const numerics_template<T>& a, const numerics_template<T2>& b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] + b.values[i];
			}
		}
		template <class T2, class T3>
		static void sub(const numerics_template<T>& a, const numerics_template<T2>& b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] - b.values[i];
			}
		}
		template <class T2, class T3>
		static void mult(const numerics_template<T>& a, const numerics_template<T2>& b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] * b.values[i];
			}
		}
		template <class T2, class T3>
		static void div(const numerics_template<T>& a, const numerics_template<T2>& b, numerics_template<T3>& out)
		{
			for (int i = 0; i < a.N; ++i)
			{
				out.values[i] = a.values[i] / b.values[i];
			}
		}
		

		template <class T2, class T3>
		numerics_template<T3> operator>(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::gt(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator>=(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::gte(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator<(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::lt(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator<=(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::lte(*this, b, out);
			return out;
		}

		

		template <class T2, class T3>
		numerics_template<T3> operator>(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::gt(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator>=(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::gte(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator<(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::lt(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator<=(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::lte(*this, b, out);
			return out;
		}






		template <class T2>
		numerics_template<T>& operator+=(const T2 b) 
		{
			numerics_template<T>::add(*this, b, *this);
			return *this;
		}
		template <class T2>
		numerics_template<T>& operator-=(const T2 b) 
		{
			numerics_template<T>::sub(*this, b, *this);
			return *this;
		}
		template <class T2>
		numerics_template<T>& operator*=(const T2 b) 
		{
			numerics_template<T>::mult(*this, b, *this);
			return *this;
		}
		template <class T2>
		numerics_template<T>& operator/=(const T2 b) 
		{
			numerics_template<T>::div(*this, b, *this);
			return *this;
		}


		template <class T2>
		numerics_template<T>& operator+=(const numerics_template<T2>& b) 
		{
			numerics_template<T>::add(*this, b, *this);
			return *this;
		}
		template <class T2>
		numerics_template<T>& operator-=(const numerics_template<T2>& b) 
		{
			numerics_template<T>::sub(*this, b, *this);
			return *this;
		}
		template <class T2>
		numerics_template<T>& operator*=(const numerics_template<T2>& b) 
		{
			numerics_template<T>::mult(*this, b, *this);
			return *this;
		}
		template <class T2>
		numerics_template<T>& operator/=(const numerics_template<T2>& b) 
		{
			numerics_template<T>::div(*this, b, *this);
			return *this;
		}

		// NOTE: prefix increment/decrement
		numerics_template<T>& operator++()  
		{  
			numerics_template<T>::add(*this, 1, *this);
			return *this;
		}  
		numerics_template<T>& operator--()  
		{  
			numerics_template<T>::add(*this, 1, *this);
			return *this;
		}  

		// NOTE: postfix increment/decrement
		numerics_template<T> operator++(int)  
		{  
			numerics_template<T>::add(*this, 1, *this);
			return *this;
		}  
		numerics_template<T> operator--(int)  
		{  
			numerics_template<T>::add(*this, 1, *this);
			return *this;
		}  
		




		template <class T2, class T3>
		numerics_template<T3> operator+(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::add(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator-(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::sub(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T> operator*(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::mult(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator/(const T2 b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::div(*this, b, out);
			return out;
		}


		template <class T2, class T3>
		numerics_template<T3> operator+(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::add(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator-(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::sub(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator*(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::mult(*this, b, out);
			return out;
		}
		template <class T2, class T3>
		numerics_template<T3> operator/(const numerics_template<T2>& b) const
		{
			numerics_template<T3> out = numerics_template<T3>(this->N);
			numerics_template<T>::div(*this, b, out);
			return out;
		}
	};

	using floats = numerics_template<float>;
	using ints = numerics_template<vec3_template<int>>;
	using uints = numerics_template<vec3_template<unsigned int>>;

}
