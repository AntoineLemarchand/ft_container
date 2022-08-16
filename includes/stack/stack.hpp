#pragma once
#include "../vector/vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> > class stack
	{
		protected:
			Container	c;

		public:
			 typedef Container						container_type;
			 typedef typename Container::value_type			value_type;
			 typedef typename Container::size_type			size_type;

			// CONSTRUCTOR
			explicit stack (const Container& ctnr = Container())
			{
				this->c = ctnr;
			}

			// MEMBER FUNCTIONS
			bool empty() const
			{
				return (c.empty());
			}

			std::size_t size() const
			{
				return (c.size());
			}

			T& top()
			{
				return (c.back());
			}

			const T& top() const
			{
				return (c.back());
			}

			void push (const T& val)
			{
				c.push_back(val);
			}

			void pop()
			{
				c.pop_back();
			}

			// OPERATORS OVERLOAD
			friend bool operator == (const stack<T,Container>& lhs,
					const stack<T,Container>& rhs)
				{
					return (lhs.c == rhs.c);
				}

			friend bool operator != (const stack<T,Container>& lhs,
					const stack<T,Container>& rhs)
				{
					return (lhs.c != rhs.c);
				}
			friend bool operator >= (const stack<T,Container>& lhs,
					const stack<T,Container>& rhs)
				{
					return (lhs.c >= rhs.c);
				}

			friend bool operator > (const stack<T,Container>& lhs,
					const stack<T,Container>& rhs)
				{
					return (lhs.c > rhs.c);
				}

			friend bool operator <= (const stack<T,Container>& lhs,
					const stack<T,Container>& rhs)
				{
					return (lhs.c <= rhs.c);
				}

			friend bool operator < (const stack<T,Container>& lhs,
					const stack<T,Container>& rhs)
				{
					return (lhs.c < rhs.c);
				}
	};

}
