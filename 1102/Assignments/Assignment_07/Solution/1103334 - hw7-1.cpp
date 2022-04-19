#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
using std::strlen;

// vector standard header
#ifndef VECTOR_H
#define VECTOR_H

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

	vector()
		: myData()
	{
	}

	vector(const size_type count)
		: myData()
	{

		myData.myFirst = new value_type[count]();
		myData.myLast = myData.myFirst + count;
		myData.myEnd = myData.myEnd;

	}

	vector(const vector& right)
		: myData()
	{

		size_type rightSize = right.size();
		myData.myFirst = new value_type[rightSize]();
		myData.myEnd = myData.myLast = myData.myFirst + rightSize;

		for (size_type i = 0; i < rightSize; i++)
			myData.myFirst[i] = *(right.myData.myFirst + i);

	}

	~vector()
	{
		if (myData.myFirst != nullptr)
			delete[] myData.myFirst;
	}

	void push_back(const Ty& val)
	{
		size_type originalSize = size();
		resize(originalSize + 1);
		myData.myFirst[originalSize] = val;
	}

	vector& operator=(const vector& right)
	{
		if (this != &right) // avoid self-assignment
		{
			size_type rightSize = right.size();
			if (rightSize > capacity())
			{

				delete[] myData.myFirst;

				size_type newCapacity = capacity() * 3 / 2;
				if (newCapacity < rightSize)
					newCapacity = rightSize;

				myData.myFirst = new value_type[newCapacity];

				myData.myEnd = myData.myFirst + newCapacity;

			}
			myData.myLast = myData.myFirst + rightSize;

			for (size_type i = 0; i < rightSize; i++)
				myData.myFirst[i] = *(right.myData.myFirst + i);

		}

		return *this; // enables x = y = z, for example
	}

	void resize(const size_type newSize)
	{
		size_type originalSize = size();
		if (newSize > originalSize)
		{
			if (newSize > capacity())
			{
				size_type newCapacity = capacity() * 3 / 2;
				if (newCapacity < newSize)
					newCapacity = newSize;

				pointer temp = new value_type[newCapacity]();

				for (size_type i = 0; i < originalSize; i++)
					temp[i] = *(myData.myFirst + i);

				myData.myFirst = &temp[0];

				myData.myEnd = myData.myFirst + newCapacity;

				myData.myLast = myData.myFirst + newSize;

			}
			else
				myData.myLast = myData.myFirst + newSize;

		}
		else
			myData.myLast = myData.myFirst + newSize;

	}

	void pop_back()
	{
		if (size() > 0)
			--myData.myLast;
	}

	void clear()
	{
		myData.myLast = myData.myFirst;
	}

	iterator begin()
	{
		return iterator(myData.myFirst);
	}

	iterator end()
	{
		return iterator(myData.myLast);
	}

	bool empty() const
	{
		return myData.myFirst == myData.myLast;
	}

	size_type size() const
	{
		return static_cast<size_type>(myData.myLast - myData.myFirst);
	}

	size_type capacity() const
	{
		return static_cast<size_type>(myData.myEnd - myData.myFirst);
	}

	value_type& front()
	{
		return *myData.myFirst;
	}

	const value_type& front() const
	{
		return *myData.myFirst;
	}

	value_type& back()
	{
		return myData.myLast[-1];
	}

	const value_type& back() const
	{
		return myData.myLast[-1];
	}

private:

	ScaryVal myData;
};

// determine if two vectors are equal and return true, otherwise return false
template< typename Ty >
bool operator==(vector< Ty >& left, vector< Ty >& right)
{
	if (left.size() != right.size())
		return false; // vectors of different number of elements

	typename vector< Ty >::iterator it1 = left.begin();
	typename vector< Ty >::iterator it2 = right.begin();
	for (; it1 != left.end(); ++it1, ++it2)
		if (*it1 != *it2)
			return false; // vector contents are not equal

	return true; // vector contents are equal
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=(vector< Ty >& left, vector< Ty >& right)
{
	return !(left == right);
}

#endif // VECTOR_H


// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

template< typename T >
class HugeInteger
{
	template< typename U >
	friend ostream& operator<<(ostream& output, HugeInteger< U > hugeInteger);
public:
	using value_type = typename T::value_type;
	using size_type = typename T::size_type;

	HugeInteger(unsigned int n = 0); // constructor; construct a zero HugeInteger with size n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	// constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const T& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	bool operator==(HugeInteger& right); // less than or equal to

	bool operator<(HugeInteger& right);  // less than

	bool operator<=(HugeInteger& right); // less than or equal to

	HugeInteger square(value_type powerTwo); // the square of HugeInteger
	HugeInteger squareRoot(value_type powerTwo); // the square root of HugeInteger

	bool isZero();           // return true if and only if all digits are zero
private:
	T integer;
}; // end class HugeInteger

#endif

// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const T& integerToCopy)
	: integer(integerToCopy)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
} // end function operator==

// function that tests if one HugeInteger is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{

	if (integer.size() != right.integer.size())
		return integer.size() < right.integer.size();
	else
		for (int i = integer.size()-1; i >= 0; i--)
		{
			if (*(right.integer.begin() + i) != *(integer.begin() + i))
				return *(integer.begin() + i) < *(right.integer.begin() + i);
		}

	return false;


} // end function operator<

// function that tests if one HugeInteger is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

template< typename T >
HugeInteger< T > HugeInteger< T >::square(value_type powerTwo)
{
	HugeInteger zero;
	if (isZero())
		return zero;

	size_t squareSize = 2 * integer.size();
	HugeInteger square(squareSize);

	for (int i = 0; i < integer.size(); i++)
		for (int j = 0; j < integer.size(); j++)
		{
			*(square.integer.begin() + i + j) += *(integer.begin() + i) * *(integer.begin() + j);
		}

	for (int i = 0; i < square.integer.size() - 1; i++)
	{
		if (*(square.integer.begin() + i) > powerTwo - 1)
		{
			*(square.integer.begin() + i + 1) += *(square.integer.begin() + i) / powerTwo;
			*(square.integer.begin() + i) %= powerTwo;
		}
	}

	while (*(square.integer.end() - 1) == 0 && square.integer.size()>1)
	{
		square.integer.resize(square.integer.size() - 1);
	}

	return square;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::squareRoot(value_type powerTwo)
{
	HugeInteger zero;
	if (isZero())
		return zero;

	size_type sqrtSize = (integer.size() + 1) / 2;
	HugeInteger sqrt(sqrtSize);

	for (int i = sqrtSize - 1; i >= 0; i--)
	{
		value_type high = powerTwo, low = 1;

		while (high >= low)
		{
			value_type middle = (high + low) / 2;

			*(sqrt.integer.begin() + i) = middle;
			
			HugeInteger tmp = sqrt.square(powerTwo);

		//	cout << *this << endl;;

			if (*this < tmp)
				high = middle - 1;
			else if (*this == tmp)
				return sqrt;
			else
				low = middle + 1;

			*(sqrt.integer.begin() + i) = low - 1;
		}

	}


	return sqrt;
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	typename T::iterator it = integer.begin();
	for (; it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	typename T::value_type numDigits = sizeof(typename T::value_type) - 1;
	typename T::iterator it = hugeInteger.integer.end() - 1;
	output << *it;
	for (--it; it != hugeInteger.integer.begin() - 1; --it)
		output << setw(numDigits) << setfill('0') << *it;

	return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
	char buf[1002];
	int numCases;
	cin >> numCases;
	for (int i = 1; i <= numCases; ++i)
	{
		cin >> buf;

		T digits[1001] = {};
		size_t last = strlen(buf) - 1;
		for (size_t i = 0; i <= last; ++i)
			digits[i] = static_cast<T>(buf[last - i]) - '0';

		vector< T > integer;
		T powerTwo;
		size_t numDigits = sizeof(T) - 1;
		for (size_t i = 0; i <= last; i += numDigits)
		{
			powerTwo = 1;
			T bigDigit = 0;
			for (size_t j = i; j < i + numDigits; ++j, powerTwo *= 10)
				bigDigit += digits[j] * powerTwo;

			integer.push_back(bigDigit);
		}

		HugeInteger< vector< T > > hugeInteger(integer);

		cout << hugeInteger.squareRoot(powerTwo) << endl;

		if (i < numCases)
			cout << endl;
	}
}

int main()
{
	int choice = 1;
	switch (choice)
	{
	case 1:
		solution< int >();
		break;
	case 2:
		solution< unsigned int >();
		break;
	case 3:
		solution< long int >();
		break;
	case 4:
		solution< unsigned long int >();
		break;
	case 5:
		solution< long long int >();
		break;
	case 6:
		solution< unsigned long long int >();
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
}