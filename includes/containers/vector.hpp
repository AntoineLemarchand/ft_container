#pragma once

template < class T, class Alloc = std::allocator<T> >
class vector
{
	// CONSTRUCTORS
	explicit vector(const Alloc& alloc = Alloc());
	explicit vector(std::size_t n, const T& val = T(),
		const Alloc& alloc = Alloc());
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
		const Alloc& alloc = Alloc());
	vector(const vector& x);

	// DESTRUCTOR
	~vector();

	// OPERATOR=
	vector&	operator= (const vector& x);

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
bool operator== (const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs);
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
