#pragma once

namespace ft
{
	template <class T1, class T2>
		struct pair
		{
			typedef T1 first_type;
			typedef T2 second_type;

			first_type	first;
			second_type	second;

			pair(): first(), second() {}

			pair( const T1& x, const T2& y): first(x), second(y) {}

			template< class U, class V >
				pair( const pair<U, V>& pr ): first(pr.first), second(pr.second)
				{}

			pair& operator=( const pair& other );
		};

	template< class T1, class T2 >
		ft::pair<T1,T2> make_pair( T1 t, T2 u )
		{
			return (pair<T1,T2>(t, u));
		}

	template< class T1, class T2 >
		bool operator == ( const ft::pair<T1,T2>& lhs,
				const ft::pair<T1,T2>& rhs )
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

	template< class T1, class T2 >
		bool operator != ( const ft::pair<T1,T2>& lhs,
				const ft::pair<T1,T2>& rhs )
		{
			return (!(lhs == rhs));
		}

	template< class T1, class T2 >
		bool operator < ( const ft::pair<T1,T2>& lhs,
				const ft::pair<T1,T2>& rhs )
		{
			return (lhs.first < rhs.first 
					|| (!(rhs.first<lhs.first) && lhs.second<rhs.second));
		}

	template< class T1, class T2 >
		bool operator <= ( const ft::pair<T1,T2>& lhs,
				const ft::pair<T1,T2>& rhs )
		{
			return (lhs == rhs || lhs < rhs);
		}

	template< class T1, class T2 >
		bool operator > ( const ft::pair<T1,T2>& lhs,
				const ft::pair<T1,T2>& rhs )
		{
			return (!(lhs <= rhs));
		}

	template< class T1, class T2 >
		bool operator >= ( const ft::pair<T1,T2>& lhs,
				const ft::pair<T1,T2>& rhs )
		{
			return (!(lhs < rhs));
		}
}
