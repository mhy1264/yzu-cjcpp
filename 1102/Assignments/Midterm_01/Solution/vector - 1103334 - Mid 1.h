// vector standard header

#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
	using value_type = ValueType;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	VectorVal()
		: myFirst(),
		myLast(),
		myEnd()
	{
	}

	pointer myFirst; // pointer to beginning of array
	pointer myLast;  // pointer to current end of sequence
	pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
	using value_type = Ty;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = Ty&;
	using const_reference = const Ty&;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

private:
	using ScaryVal = VectorVal< Ty >;

public:
	using iterator = value_type*;
	using const_iterator = const value_type*;

	// empty container constructor (default constructor)
	// Constructs an empty container, with no elements.
	vector()
		: myData()
	{
	}

	// fill constructor
	// Constructs a container with "count" elements.
	// Each element is initialized as 0.
	vector(const size_type count)
		: myData()
	{

		myData.myFirst = new value_type[count]();
		myData.myLast = myData.myEnd = myData.myFirst + count;
	}

	// copy constructor
	// Constructs a container with a copy of each of the elements in "right",
	// in the same order.
	vector(const vector& right)
		: myData()
	{
		myData.myFirst = new value_type[static_cast<size_type>(right.capacity())]();

		myData.myLast = myData.myFirst + right.size();

		myData.myEnd = myData.myFirst + right.size();

		for (size_type i = 0; i < static_cast<size_type>(right.size()); i++)
			myData.myFirst[i] = right[i];
	}

	// Vector destructor
	// Destroys the container object.
	// Deallocates all the storage capacity allocated by the vector.
	~vector()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	// The vector is extended by inserting a new element before the element
	// at the specified position, effectively increasing the container size by one.
	// This causes an automatic reallocation of the allocated storage space
	// if and only if the new vector size surpasses the current vector capacity.
	// Relocates all the elements that were after "where" to their new positions.
	iterator insert(const_iterator where, const value_type& val)
	{

		if (where >= myData.myFirst && where <= myData.myLast)
		{
			//cout << " 1 " ;
			size_type originalSize = size();
			size_type originalCapacity = capacity();
			if (originalSize == originalCapacity)
			{
				size_type newCapacity;
				if (originalCapacity <= 1)
					newCapacity = originalCapacity + 1;
				else
					newCapacity = originalCapacity * 3 / 2;

				pointer temp = new value_type[newCapacity + 1];

				int target = where- begin() ;
				int i, t;

				for (i = 0, t = 0; i < target; i++, t++)
					temp[i] = myData.myFirst[i];

				temp[i++] = val;

				for (; t < originalSize; i++, t++)
					temp[i] = myData.myFirst[t];

				myData.myFirst = temp;
				myData.myLast = myData.myFirst + originalSize + 1;
				myData.myEnd = myData.myFirst + newCapacity;

				return myData.myFirst + target;

			}
			else
			{
				int target = where - begin();

				pointer temp = new value_type[originalSize];

				for (int i = 0; i < originalSize; i++)
					temp[i] = myData.myFirst[i];
				
				myData.myFirst[target] = val;

				for (int i = target; i < originalSize + 1; i++)
					myData.myFirst[i+1] = temp[i];

				myData.myLast = myData.myFirst + originalSize + 1;

				delete[] temp;
				return myData.myFirst + target;

			}
		}
		else
			return nullptr;
	}

	// Removes from the vector either a single element (where).
	// This effectively reduces the container size by one, which is destroyed.
	// Relocates all the elements after the element erased to their new positions.
	iterator erase(const_iterator where)
	{
		if (where >= myData.myFirst && where < myData.myLast)
		{
			size_type originalSize = size();
			int target = where - begin();

			pointer temp = new value_type[originalSize];

			for (int i = 0; i < originalSize; i++)
				temp[i] = myData.myFirst[i];

			for (int i = target; i < originalSize-1; i++)
				myData.myFirst[i] = temp[i+1];

			myData.myLast = myData.myFirst + originalSize - 1;
			delete[] temp;

			return iterator(where);
		}
		else
			return nullptr;
	}

	// Removes all elements from the vector (which are destroyed),
	// leaving the container with a size of 0.
	// A reallocation is not guaranteed to happen,
	// and the vector capacity is not guaranteed to change due to calling this function.
	void clear() // erase all
	{
		myData.myLast = myData.myFirst;
	}

	// Returns an iterator pointing to the first element in the vector.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	iterator begin()
	{
		return myData.myFirst;
	}

	// Returns an iterator pointing to the first element in the vector.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	const_iterator begin() const
	{
		return const_iterator(myData.myFirst);
	}

	// Returns an iterator referring to the past-the-end element in the vector container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as vector::begin.
	iterator end()
	{
		return myData.myLast;
	}

	// Returns an iterator referring to the past-the-end element in the vector container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the vector.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as vector::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myLast);
	}

	// Returns whether the vector is empty (i.e. whether its size is 0).
	bool empty() const
	{
		return myData.myFirst == myData.myLast;
	}

	// Returns the number of elements in the vector.
	// This is the number of actual objects held in the vector,
	// which is not necessarily equal to its storage capacity.
	size_type size() const
	{
		return static_cast<size_type>(myData.myLast - myData.myFirst);
	}

	// Returns the size of the storage space currently allocated for the vector,
	// expressed in terms of elements.
	// This capacity is not necessarily equal to the vector size.
	// It can be equal or greater, with the extra space allowing to accommodate
	// for growth without the need to reallocate on each insertion.
	size_type capacity() const
	{
		return static_cast<size_type>(myData.myEnd - myData.myFirst);
	}

	// Returns a reference to the element at position "pos" in the vector container.
	value_type& operator[](const size_type pos)
	{
		if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
		{
			cout << "vector subscript out of range\n";
			exit(1);
		}

		return myData.myFirst[pos];
	}

	// Returns a reference to the element at position "pos" in the vector container.
	const value_type& operator[](const size_type pos) const
	{
		if (pos >= static_cast<size_type>(myData.myLast - myData.myFirst))
		{
			cout << "vector subscript out of range\n";
			exit(1);
		}

		return myData.myFirst[pos];
	}

private:
	ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const vector< Ty >& left, const vector< Ty >& right)
{

	if (left.size() != right.size())
		return false;
	else
	{
		for (size_t i = 0; i < left.size(); i++)
			if (left[i] != right[i])
				return false;
		return true;
	}

}

#endif // VECTOR_H
