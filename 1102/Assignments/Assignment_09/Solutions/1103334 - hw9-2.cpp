#include <iostream>
#include <cmath>
using namespace std;

const int maxSize = 200;

template< typename BidIt >
class ReverseIterator
{
public:
	using value_type = typename BidIt::value_type;
	using difference_type = typename BidIt::difference_type;
	using pointer = typename BidIt::pointer;
	using reference = typename BidIt::reference;

	ReverseIterator() = default;

	ReverseIterator(BidIt right)
		: current(right)
	{
	}

	ReverseIterator(const ReverseIterator& right)
		: current(right.current)
	{
	}

	ReverseIterator& operator=(const ReverseIterator& right)
	{
		current = right.current;
		return *this;
	}

	BidIt base() const
	{
		return current;
	}

	reference operator*() const
	{
		BidIt tmp = current;
		return *--tmp;
	}

	ReverseIterator& operator++()
	{
		--current;
		return *this;
	}

protected:
	BidIt current{};
};

template< typename BidIt1, typename BidIt2 >
bool operator==(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return left.base() == right.base();
}

template< typename BidIt1, typename BidIt2 >
bool operator!=(const ReverseIterator< BidIt1 >& left,
	const ReverseIterator< BidIt2 >& right)
{
	return !(left == right);
}


template< typename MyVec >
class VectorConstIterator
{
public:
	using value_type = typename MyVec::value_type;
	using difference_type = typename MyVec::difference_type;
	using pointer = typename MyVec::const_pointer;
	using reference = const value_type&;
	using TPtr = typename MyVec::pointer;

	VectorConstIterator()
		: ptr()
	{
	}

	VectorConstIterator(TPtr parg)
		: ptr(parg)
	{
	}

	reference operator*() const
	{
		return *ptr;
	}

	VectorConstIterator& operator++()
	{
		++ptr;
		return *this;
	}

	VectorConstIterator& operator--()
	{
		--ptr;
		return *this;
	}

	bool operator==(const VectorConstIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const VectorConstIterator& right) const
	{
		return !(*this == right);
	}

	TPtr ptr;
};


template< typename MyVec >
class VectorIterator : public VectorConstIterator< MyVec >
{
public:
	using MyBase = VectorConstIterator< MyVec >;

	using value_type = typename MyVec::value_type;
	using difference_type = typename MyVec::difference_type;
	using pointer = typename MyVec::pointer;
	using reference = value_type&;

	using MyBase::MyBase;

	reference operator*() const
	{
		return const_cast<reference>(MyBase::operator*());
	}

	VectorIterator& operator++()
	{
		MyBase::operator++();
		return *this;
	}

	VectorIterator& operator--()
	{
		MyBase::operator--();
		return *this;
	}
};


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


template< typename Ty >
class vector
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
	using iterator = VectorIterator< ScaryVal >;
	using const_iterator = VectorConstIterator< ScaryVal >;
	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	vector()
		: myData()
	{
	}

	vector(const size_type count)
		: myData()
	{

		myData.myFirst = new value_type[count + 1]();
		myData.myLast = &(myData.myFirst[count]);
		myData.myEnd = &(myData.myFirst[count]);

	}

	vector(const vector& right)
		: myData()
	{

		myData.myFirst = new value_type[static_cast<size_type>(right.myData.myLast - right.myData.myFirst)];
		myData.myLast = myData.myFirst + static_cast<size_type>(right.myData.myLast - right.myData.myFirst);
		myData.myEnd = myData.myFirst + static_cast<size_type>(right.myData.myLast - right.myData.myFirst);

		for (int i = 0; (myData.myFirst + i) != myData.myLast; i++)
			myData.myFirst[i] = right.myData.myFirst[i];

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
		if (this != &right)
		{
			size_type rightSize = right.size();
			if (rightSize > capacity())
			{

				delete[] myData.myFirst;

				size_type newCapacity = capacity() * 3 / 2;
				if (newCapacity < rightSize)
					newCapacity = rightSize;

				myData.myFirst = new value_type[newCapacity]();

				for (int i = 0; i < rightSize; i++)
					myData.myFirst[i] = *(right.myData.myFirst + i);

				myData.myLast = myData.myFirst + rightSize;

				myData.myEnd = myData.myFirst + newCapacity;

			}
			else
			{
				for (int i = 0; i < rightSize; i++)
					myData.myFirst[i] = right.myData.myFirst[i];

				myData.myLast = myData.myFirst + (right.myData.myLast - right.myData.myFirst);
			}



		}

		return *this;
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

				pointer tempFirst = myData.myFirst;

				myData.myFirst = new value_type[newCapacity]();

				for (size_t i = 0; i < originalSize; i++)
					myData.myFirst[i] = tempFirst[i];

				delete[]tempFirst;

				myData.myEnd = myData.myFirst + newCapacity;

			}
			for (size_t i = originalSize; i < capacity(); i++)
				clear();
		}
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

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
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

	value_type& back()
	{
		return myData.myLast[-1];
	}

private:

	ScaryVal myData;
};

template< typename Ty >
bool operator==(vector< Ty >& left, vector< Ty >& right)
{
	if (left.size() != right.size())
		return false;
	else
	{
		typename vector <Ty>::iterator itLeft = left.begin();
		typename vector <Ty>::iterator itRight = right.begin();

		for (; itLeft != left.end(); ++itLeft, ++itRight)
			if (*itRight != *itLeft)
				return false;
		return true;

	}


}

template< typename Ty >
bool operator!=(vector< Ty >& left, vector< Ty >& right)
{
	return !(left == right);
}


template< typename MyList >
class ListConstIterator
{
public:
	using nodePtr = typename MyList::nodePtr;
	using value_type = typename MyList::value_type;
	using difference_type = typename MyList::difference_type;
	using pointer = typename MyList::const_pointer;
	using reference = const value_type&;

	ListConstIterator()
		: ptr()
	{
	}

	ListConstIterator(nodePtr pNode)
		: ptr(pNode)
	{
	}

	reference operator*() const
	{
		return ptr->myVal;
	}

	ListConstIterator& operator++()
	{
		ptr = ptr->next;
		return *this;
	}

	ListConstIterator& operator--()
	{
		ptr = ptr->prev;
		return *this;
	}

	bool operator==(const ListConstIterator& right) const
	{
		return ptr == right.ptr;
	}

	bool operator!=(const ListConstIterator& right) const
	{
		return !(*this == right);
	}

	nodePtr ptr;
};


template< typename MyList >
class ListIterator : public ListConstIterator< MyList >
{
public:
	using MyBase = ListConstIterator< MyList >;

	using nodePtr = typename MyList::nodePtr;
	using value_type = typename MyList::value_type;
	using difference_type = typename MyList::difference_type;
	using pointer = typename MyList::pointer;
	using reference = value_type&;

	using MyBase::MyBase;

	reference operator*() const
	{

		return const_cast<reference>(MyBase::operator*());
	}

	ListIterator& operator++()
	{
		MyBase::operator++();
		return *this;
	}

	ListIterator& operator--()
	{
		MyBase::operator--();
		return *this;
	}
};

template< typename ValueType >
struct ListNode
{
	using nodePtr = ListNode*;

	nodePtr next; // successor node, or first element if head
	nodePtr prev; // predecessor node, or last element if head
	ValueType myVal; // the stored value, unused if head
};


template< typename Ty >
class ListVal
{
public:
	using node = ListNode< Ty >;
	using nodePtr = node*;

	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	ListVal()
		: myHead(),
		mySize(0)
	{
	}

	nodePtr myHead; // pointer to head node
	size_type mySize; // number of elements
};


template< typename Ty >
class list
{
	using node = ListNode< Ty >;
	using nodePtr = node*;
	using ScaryVal = ListVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = ListIterator< ScaryVal >;
	using const_iterator = ListConstIterator< ScaryVal >;
	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	list()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
	}

	list(size_type count)
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		if (count > 0)
			for (size_type i = 0; i < count; ++i)
				push_back(Ty());
	}

	list(const list& right)
		: myData()
	{

		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;


		iterator it = right.myData.myHead->next;

		for (int i = 0; i < right.size(); ++i, ++it)
			push_back(*it);

	}

	~list()
	{
		clear();
		delete myData.myHead;
	}

	list& operator=(const list& right)
	{
		if (this != &right)
		{
			resize(right.size());

			iterator itThis = begin();
			list temp(right);
			iterator itRight = temp.begin();

			for (; itRight != temp.end(); ++itRight, ++itThis)
				*itThis = *itRight;
		}

		return *this;
	}

	iterator begin()
	{
		return iterator(myData.myHead->next);
	}

	iterator end()
	{
		return iterator(myData.myHead);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	void resize(size_type newSize)
	{
		if (myData.mySize < newSize)
		{
			size_type difference = newSize - myData.mySize;
			for (size_type i = 0; i < difference; i++)
				push_back(Ty());
		}
		else
		{
			while (newSize < myData.mySize)
				pop_back();
		}
	}

	size_type size() const
	{
		return myData.mySize;
	}

	reference front()
	{
		return myData.myHead->next->myVal;
	}

	reference back()
	{
		return myData.myHead->prev->myVal;
	}

	void push_back(const Ty& val)
	{

		myData.mySize++;

		nodePtr temp = new node;
		temp->myVal = val;

		temp->next = myData.myHead;
		temp->prev = myData.myHead->prev;

		myData.myHead->prev->next = temp;
		myData.myHead->prev = temp;

	}

	void pop_back()
	{
		if (myData.mySize > 0)
		{

			node* deleted = myData.myHead->prev;

			deleted->prev->next = deleted->next;
			myData.myHead->prev = deleted->prev;

			delete deleted;

			myData.mySize--;

		}
	}

	void clear()
	{
		if (myData.mySize != 0)
		{

			while (myData.mySize != 0)
				pop_back();

		}
	}

private:
	ScaryVal myData;
};

template< typename Ty >
bool operator==(list< Ty >& left, list< Ty >& right)
{

	if (left.size() != right.size())
		return false;

	typename list<Ty>::iterator itLeft = left.begin();
	typename list<Ty>::iterator itRight = right.begin();

	for (; itLeft != left.end(); ++itLeft, ++itRight)
		if (*itLeft != *itRight)
			return false;
	return true;

}

template< typename Ty >
bool operator!=(list< Ty >& left, list< Ty >& right)
{
	return !(left == right);
}


template< typename MyDeque >
class DequeConstIterator
{
private:
	using size_type = typename MyDeque::size_type;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::const_pointer;
	using reference = const value_type&;

	DequeConstIterator()
		: myOff(0),
		myCont(nullptr)
	{
	}

	DequeConstIterator(size_type off, const MyDeque* pDeque)
		: myOff(off),
		myCont(pDeque)
	{
	}

	DequeConstIterator(const DequeConstIterator& right)
		: myOff(right.myOff),
		myCont(right.myCont)
	{
	}

	~DequeConstIterator()
	{
	}

	const DequeConstIterator& operator=(const DequeConstIterator& right)
	{
		if (&right != this)
		{
			myCont = right.myCont;
			myOff = right.myOff;
		}
		return *this;
	}

	reference operator*() const
	{
		//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
		size_type block = myCont->getBlock(myOff);
		size_type off = myOff % 4;
		return myCont->map[block][off];
	}

	DequeConstIterator& operator++()
	{
		++myOff;
		return *this;
	}

	DequeConstIterator& operator--()
	{
		--myOff;
		return *this;
	}

	DequeConstIterator& operator+=(const difference_type off)
	{
		myOff += off;
		return *this;
	}

	DequeConstIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	bool operator==(const DequeConstIterator& right) const
	{
		return this->myCont == right.myCont && this->myOff == right.myOff;
	}

	bool operator!=(const DequeConstIterator& right) const
	{
		return !(*this == right);
	}

	const MyDeque* myCont; // keep a pointer to deque
	size_type myOff;       // offset of element in deque
};


template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{
private:
	using size_type = typename MyDeque::size_type;
	using MyBase = DequeConstIterator< MyDeque >;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::pointer;
	using reference = value_type&;

	DequeIterator()
	{
	}

	DequeIterator(size_type off, const MyDeque* pDeque)
		: MyBase(off, pDeque)
	{
	}

	reference operator*() const
	{
		return const_cast<reference>(MyBase::operator*());
	}

	DequeIterator& operator++()
	{
		MyBase::operator++();
		return *this;
	}

	DequeIterator& operator--()
	{
		MyBase::operator--();
		return *this;
	}

	DequeIterator& operator-=(const difference_type off)
	{
		MyBase::operator-=(off);
		return *this;
	}

	DequeIterator operator-(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp -= off;
	}
};

template< typename Ty >
class DequeVal
{
public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using MapPtr = Ty**;

	DequeVal()
		: map(),
		mapSize(0),
		myOff(0),
		mySize(0)
	{
	}

	size_type getBlock(size_type off) const
	{
		return off % (4 * mapSize) / 4;
		//      return ( off / 4 ) & ( mapSize - 1 );
	}

	MapPtr map;        // pointer to array of pointers to blocks
	size_type mapSize; // size of map array, zero or 2^N
	size_type myOff;   // offset of initial element
	size_type mySize;  // current length of sequence
};


template< typename Ty >
class deque
{
private:
	using MapPtr = Ty**;
	using ScaryVal = DequeVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = DequeIterator< ScaryVal >;
	using const_iterator = DequeConstIterator< ScaryVal >;

	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	deque()
		: myData()
	{
	}

	deque(size_type count)
		: myData()
	{
		resize(count);
	}

	deque(const deque& right)
		: myData()
	{
		myData.myOff = 0;
		myData.mySize = right.myData.mySize;
		myData.mapSize = right.myData.mapSize;
		if (right.myData.mySize > 4 * (right.myData.mapSize - 1))
			myData.mapSize = right.myData.mapSize * 2;

		if (myData.mySize != 0)
			myData.map = new value_type * [myData.mapSize];

		for (int i = 0; i < myData.mapSize; i++)
			myData.map[i] = new value_type[4];


		iterator it1(myData.myOff, &myData);
		iterator it2(right.myData.myOff, &right.myData);

		for (int i = 0; i < myData.mySize; i++, ++it1, ++it2)
			*it1 = *it2;

	}

	~deque()
	{
		clear();
	}

	deque& operator=(const deque& right)
	{
		if (&right != this)
		{
			this->myData.mySize = 0;
			iterator it1(right.myData.myOff, &right.myData);
			for (int i = 0; i < right.size(); i++)
			{
				push_back(*it1);
				++it1;
			}

		}

		return *this;
	}

	iterator begin()
	{
		return iterator(myData.myOff, &myData);
	}

	iterator end()
	{
		return iterator(myData.myOff + myData.mySize, &myData);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	void resize(size_type newSize)
	{
		while (myData.mySize < newSize)
			push_back(value_type());

		while (newSize < myData.mySize)
			pop_back();
	}

	size_type size() const
	{
		return myData.mySize;
	}

	reference front()
	{
		return *begin();
	}

	reference back()
	{
		return *(end() - 1);
	}

	void push_back(const value_type& val)
	{
		if (myData.mySize == 0)
		{

			if (myData.mapSize == 0)
				myData.mapSize = 8;

			myData.map = new Ty * [myData.mapSize]();
			myData.map[0] = new Ty[4]();
			myData.map[0][0] = val;

		}
		else
		{
			size_type newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
			if (newBack % 4 == 0 && myData.mySize >= 4 * (myData.mapSize - 1))
			{
				doubleMapSize();
				newBack = myData.myOff + myData.mySize;
			}
			else

				if (myData.myOff >= 4 * myData.mapSize)
					myData.myOff %= 4 * myData.mapSize;

			if (newBack % 4 == 0)
				myData.map[newBack / 4] = new Ty[4];

			myData.map[newBack / 4][newBack % 4] = val;
		}

		++myData.mySize;
	}

	void pop_back()
	{
		size_type back = (myData.myOff + myData.mySize - 1) % (4 * myData.mapSize);
		if (back % 4 == 0)
		{
			size_type front = myData.myOff % (4 * myData.mapSize);
			if (front > back && front <= back + 3)
			{
				delete[] myData.map[back / 4];
				myData.map[back / 4] = nullptr;
			}
		}

		--myData.mySize;
		if (myData.mySize == 0)
			myData.myOff = 0;
	}

	void clear()
	{
		if (myData.mapSize > 0)
		{
			for (size_type i = 0; i < myData.mapSize; i++)
				if (myData.map[i] != nullptr)
					delete[] myData.map[i];
			delete[] myData.map;

			myData.mapSize = 0;
			myData.mySize = 0;
			myData.myOff = 0;
			myData.map = MapPtr();
		}
	}

private:

	size_type getBlock(size_type off) const
	{
		return myData.getBlock(off);
		//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
	}

	void doubleMapSize()
	{
		size_type i = 0;
		size_type newSize = myData.mapSize * 2;
		size_type startRow = myData.myOff / 4;
		size_type total = 0; // notnull 的行數

		MapPtr buffer = new Ty * [newSize];

		for (i = 0; i < newSize; i++) // 都變成 nullptr
			buffer[i] = nullptr;

		for (i = 0; i < myData.mapSize; i++)
			if (myData.map[i] != nullptr)
				total++;

		for (i = startRow; i < startRow + total; i++)
			buffer[i] = new Ty[4]();

		size_type count = 0;
		for (i = startRow; i < myData.mapSize and count < total; count++, i++) // 後半段
		{
			for (size_type j = 0; j < 4; j++)
			{
				buffer[count + startRow][j] = myData.map[i][j];
			}
		}

		for (i = 0; count < total; count++, i++)
		{
			for (size_type j = 0; j < 4; j++)
			{
				buffer[count + startRow][j] = myData.map[i][j];
			}
		}

		delete[] myData.map;
		//改變設定值
		myData.mapSize = newSize;
		myData.map = buffer;


	}

	ScaryVal myData;
};

template< typename Ty >
bool operator==(deque< Ty >& left, deque< Ty >& right)
{

	if (left.size() != right.size())
		return false;

	typename deque<Ty>::iterator itLeft = left.begin();
	typename deque<Ty>::iterator itRight = right.begin();
	for (; itLeft != left.end(); ++itLeft, ++itRight)
	{
//		cout << *itLeft << " " << *itRight << endl;
		if (*itLeft != *itRight)
			return false;
	}


	return true;

}


template< typename T >
class HugeInteger
{
	template< typename U >
	friend ostream& operator<<(ostream& output, HugeInteger< U >& hugeInteger);
public:
	using value_type = typename T::value_type;
	using size_type = typename T::size_type;

	HugeInteger(size_type n = 0);
	HugeInteger(const HugeInteger& integerToCopy);
	~HugeInteger();
	const HugeInteger& operator=(const HugeInteger& right);
	bool operator==(HugeInteger& right);
	bool operator<(HugeInteger& right);
	bool operator<=(HugeInteger& right);
	void operator-=(HugeInteger& op2);
	void operator*=(HugeInteger& op2);
	HugeInteger operator/(HugeInteger& op2);
	HugeInteger operator%(HugeInteger& op2);
	HugeInteger& operator--();
	void convert(const value_type& number);
	void power(HugeInteger& base, const value_type& expon);
	size_type size();
	bool isZero();
	bool leadingZero();
private:
	T integer;
	void divideByTen();
	void helpDecrement();
};


template< typename T >
HugeInteger< T >::HugeInteger(size_type n)
	: integer((n == 0) ? 1 : n)
{
}

template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger& right)
{
	if (&right != this)
		integer = right.integer;

	return *this;
}

template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
}

template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
{

	if (integer.size() != right.integer.size())
		return integer.size() < right.integer.size();

	typename T::reverse_iterator it = integer.rbegin();
	typename T::reverse_iterator itRight = right.integer.rbegin();

	for (; it != integer.rend(); ++it, ++itRight)
		if (*it != *itRight)
			return *it < *itRight;

	return false;

} // end function operator<

template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

template< typename T >
void HugeInteger< T >::operator-=(HugeInteger& op2)
{
	HugeInteger zero;

	//cout << *this << endl;
	//cout << op2 << endl;
	if (*this == op2)
	{
		*this = zero;
		return;
	}

	HugeInteger difference(*this);

	typename T::iterator it1 = difference.integer.begin();
	typename T::iterator it2 = op2.integer.begin();

	for (; it2 != op2.integer.end(); ++it1, ++it2)
		*it1 -= *it2;

	for (it1 = difference.integer.begin(); it1 != difference.integer.end(); ++it1)
		if (*it1 < 0 || *it1>9)
		{
			*it1 += 10;
			typename T::iterator temp = it1;
			++temp;
			*temp -= 1;
		}

	while (difference.leadingZero())
		difference.integer.pop_back();

	if (difference.leadingZero())
		cout << "difference has a leading zero!\n";

	*this = difference;
}

template< typename T >
void HugeInteger< T >::operator*=(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
	{
		*this = zero;
		return;
	}

	HugeInteger product(integer.size() + op2.integer.size());

	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = op2.integer.begin();
	typename T::iterator it3 = product.integer.begin();
	int i = 0, j = 0;

	for (i = 0, it1 = integer.begin(); it1 != integer.end(); ++it1, ++i)
		for (j = 0, it2 = op2.integer.begin(); it2 != op2.integer.end(); ++it2, ++j)
		{
			it3 = product.integer.begin();

			int count = i + j;
			for (int t = 0; t < count; t++)
				++it3;

			*it3 += *it1 * *it2;

			if (*it3 > 9)
			{
				typename T::iterator temp = it3;
				++temp; // the next digit of the prodcut 
				*temp += *it3 / 10;
				*it3 %= 10;
			}
		}

	while (product.leadingZero())
		product.integer.pop_back();


	if (product.leadingZero())
		cout << "product has a leading zero!\n";

	////cout << "* ==> " << product << endl;
	*this = product;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;
	HugeInteger remainder = *this;
	HugeInteger buffer = op2;

	size_type Size = remainder.size() - buffer.size();

	HugeInteger ten(2);
	ten.convert(10);

	for (int i = 0; i < Size; i++)
		buffer *= ten;

	//cout << buffer << endl;

	size_type quotientSize = this->integer.size() - op2.integer.size();

	if (remainder < buffer)
		buffer.divideByTen();
	else
		quotientSize++;
	
	HugeInteger quotient(quotientSize);

	typename T::reverse_iterator it1 = quotient.integer.rbegin();
	for (; it1 != quotient.integer.rend(); ++it1)
	{

		while (buffer <= remainder)
		{
			remainder -= buffer;
			(*it1)++;
		}
		buffer.divideByTen();
	}

//	cout << "/ ==> "<<quotient << endl;

	return quotient;
}

template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger& op2)
{
	HugeInteger remainder = *this;
	HugeInteger quotient = (*this) / op2;
	quotient *= op2;
	remainder -= quotient;
	return remainder;
}

template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
	helpDecrement();
	return *this;
}

template< typename T >
void HugeInteger< T >::convert(const value_type& number)
{
	size_type numDigits = 0;
	typename T::iterator it = integer.begin();
	for (value_type i = number; i > 0; i /= 10, ++it, ++numDigits)
		*it = i % 10;
	integer.resize(numDigits);
}

template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = it1;
	for (++it2; it2 != integer.end(); ++it1, ++it2)
		*it1 = *it2;
	integer.pop_back();
}

template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename T::iterator it = integer.begin();
	for (; *it == 0; ++it)
		*it = 9;

	--(*it);

	if (leadingZero())
		integer.pop_back();
}

template< typename T >
void HugeInteger< T >::power(HugeInteger& base, const value_type& expon)
{
	*integer.begin() = 1;
	for (value_type i = 0; i < expon; ++i)
	{
		*this *= base;
		if (integer.size() > maxSize - base.integer.size())
			break;
	}
}

template< typename T >
typename HugeInteger< T >::size_type HugeInteger< T >::size()
{
	return integer.size();
}

template< typename T >
bool HugeInteger< T >::isZero()
{
	return (integer.size() == 1 && integer.front() == 0);
}

template< typename T >
bool HugeInteger< T >::leadingZero()
{
	return (integer.size() > 1 && integer.back() == 0);
}

template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T >& hugeInteger)
{
	typename T::reverse_iterator it = hugeInteger.integer.rbegin();
	for (; it != hugeInteger.integer.rend(); ++it)
		if (*it < 10)
			output << *it;

	return output;
}

template< typename T1, typename T2 >
void solution2()
{
	T2 t, a, b;
	while (cin >> t >> a >> b)
	{
		cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

		if (t == 1)
			cout << "is not an integer with less than 100 digits.\n";
		else if (a == b)
			cout << "1\n";
		else if (a < b)
			cout << "is not an integer with less than 100 digits.\n";
		else if (a % b != 0)
			cout << "is not an integer with less than 100 digits.\n";
		else if ((a - b) * static_cast<T2>(log10(t)) > 95)
			cout << "is not an integer with less than 100 digits.\n";
		else
		{
			HugeInteger< T1 > base(10);
			base.convert(t); // put all digits of t into base

			HugeInteger< T1 > dividend(1);
			dividend.power(base, a); // dividend = pow( t, a )

			if (dividend.size() > maxSize - base.size())
				cout << "is not an integer with less than 100 digits.\n";
			else
			{
				HugeInteger< T1 > divisor(1);
				divisor.power(base, b); // divisor = pow( t, b )

				if (divisor.size() > maxSize - base.size())
					cout << "is not an integer with less than 100 digits.\n";
				else
				{
					--dividend; // pow( t, a ) - 1
					--divisor;  // pow( t, b ) - 1

					//cout << endl;
					//cout << dividend << endl;
					//cout << divisor << endl;

					HugeInteger< T1 > quotient = dividend / divisor;
					HugeInteger< T1 > remainder = dividend % divisor;

					//cout << remainder << endl;

					if (quotient.leadingZero())
						cout << "quotient has a leading zero!\n";

					if (remainder.leadingZero())
						cout << "remainder has a leading zero!\n";

					// quotient is an integer with less than 100 digits
					if (quotient.size() < 100 && remainder.isZero())
						cout << quotient << endl;
					else
						cout << "is not an integer with less than 100 digits.\n";
				}
			}
		}
	}
}

template< typename T >
void solution1()
{
	T choice = 1;
	switch (choice)
	{
	case 1:
		solution2< vector< T >, T >();
		break;
	case 2:
		solution2< list< T >, T >();
		break;
	case 3:
		solution2< deque< T >, T >();
		break;
	default:
		cout << "Program should never get here!";
	}
}

int main()
{
	int choice = 2;
	switch (choice)
	{
	case 1:
		solution1< int >();
		break;
	case 2:
		solution1< unsigned int >();
		break;
	case 3:
		solution1< long int >();
		break;
	case 4:
		solution1< unsigned long int >();
		break;
	case 5:
		solution1< long long int >();
		break;
	case 6:
		solution1< unsigned long long int >();
		break;
	default:
		cout << "Program should never get here!";
	}

	system("pause");
}