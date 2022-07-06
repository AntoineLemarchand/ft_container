#pragma once
#include <ft_vector.hpp>

template <class T, class Container = ft_vector<T> > class ft_stack
{
	// CONSTRUCTOR
	explicit ft_stack (const Container& ctnr = Container());

	// DESTRUCTOR
	~ft_stack();

	ft_stack& operator=( const ft_stack& other );

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
bool operator== (const ft_stack<T,Container>& lhs,
	const ft_stack<T,Container>& rhs);
template <class T, class Container>
bool operator!= (const ft_stack<T,Container>& lhs,
	const ft_stack<T,Container>& rhs);
template <class T, class Container>
bool operator<  (const ft_stack<T,Container>& lhs,
	const ft_stack<T,Container>& rhs);
template <class T, class Container>
bool operator<= (const ft_stack<T,Container>& lhs,
	const ft_stack<T,Container>& rhs);
template <class T, class Container>
bool operator>  (const ft_stack<T,Container>& lhs,
	const ft_stack<T,Container>& rhs);
template <class T, class Container>
bool operator>= (const ft_stack<T,Container>& lhs,
	const ft_stack<T,Container>& rhs);
