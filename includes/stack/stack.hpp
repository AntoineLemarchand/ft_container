#pragma once
#include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > class stack
	{
		public:
			// CONSTRUCTOR
			explicit stack (const Container& ctnr = Container());

			// DESTRUCTOR
			~stack();

			stack& operator=( const stack& other );

			// MEMBER FUNCTIONS
			bool empty() const;
			std::size_t size() const;

			T& top();
			const T& top() const;

			void push (const T& val);

			void pop();
	};

	// OPERATORS OVERLOAD
	template <class T, class Container>
		bool operator== (const stack<T,Container>& lhs,
				const stack<T,Container>& rhs);
	template <class T, class Container>
		bool operator!= (const stack<T,Container>& lhs,
				const stack<T,Container>& rhs);
	template <class T, class Container>
		bool operator<  (const stack<T,Container>& lhs,
				const stack<T,Container>& rhs);
	template <class T, class Container>
		bool operator<= (const stack<T,Container>& lhs,
				const stack<T,Container>& rhs);
	template <class T, class Container>
		bool operator>  (const stack<T,Container>& lhs,
				const stack<T,Container>& rhs);
	template <class T, class Container>
		bool operator>= (const stack<T,Container>& lhs,
				const stack<T,Container>& rhs);
}
