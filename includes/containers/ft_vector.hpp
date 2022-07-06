#pragma once

template < class T, class Alloc = std::allocator<T> >
class ft_vector
{
	// CONSTRUCTORS
	explicit ft_vector(const Alloc& alloc = Alloc());
	explicit ft_vector(std::size_t n, const T& val = T(),
		const Alloc& alloc = Alloc());
	template <class ft_InputIterator>
	ft_vector(ft_InputIterator first, ft_InputIterator last,
		const Alloc& alloc = Alloc());
	ft_vector(const ft_vector& x);

	// DESTRUCTOR
	~ft_vector();

	// OPERATOR=
	ft_vector&	operator= (const ft_vector& x);

	// ITERATORS
	// TODO

	// CAPACITY
	std::size_t	size() const;
	std::size_t	max_size() const;
	void		resize (std::size_t n, T val = T());
	std::size_t	capacity() const;
	bool		empty() const;
	void		reserve (std::size_t n);

	// ELEMENT ACCESS
	T&			operator[] (std::size_t n);
	const T&	operator[] (std::size_t n) const;

	T&			at (std::size_t n);
	const T&	at (std::size_t n) const;

	T&			front();
	const T&	front() const;

	T&			back();
	const T&	back() const;

	// MODIFIERS
	// TODO

	// ALLOCATOR
	Alloc get_allocator() const;
};

// RELATIONAL ITERATOR
template <class T, class Alloc>
bool operator== (const ft_vector<T,Alloc>& lhs,
	const ft_vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator!= (const ft_vector<T,Alloc>& lhs,
	const ft_vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<  (const ft_vector<T,Alloc>& lhs,
	const ft_vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<= (const ft_vector<T,Alloc>& lhs,
	const ft_vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>  (const ft_vector<T,Alloc>& lhs,
	const ft_vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>= (const ft_vector<T,Alloc>& lhs,
	const ft_vector<T,Alloc>& rhs);
template <class T, class Alloc>
void swap (ft_vector<T,Alloc>& x, ft_vector<T,Alloc>& y);
