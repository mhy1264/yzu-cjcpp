#ifndef DEQUE_H
#define DEQUE_H

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
	using size_type = typename MyDeque::size_type;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::const_pointer;
	using reference = const value_type&;

	// construct with null pointer
	DequeConstIterator()
		: myOff(0),
		myCont(nullptr)
	{
	}

	// construct with offset off in *pDeque
	DequeConstIterator(size_type off, const MyDeque* pDeque)
		: myOff(off),
		myCont(pDeque)
	{
	}

	DequeConstIterator(const DequeConstIterator& right) // copy constructor
		: myOff(right.myOff),
		myCont(right.myCont)
	{
	}

	~DequeConstIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const DequeConstIterator& operator=(const DequeConstIterator& right)
	{
		if (&right != this) // avoid self-assignment
		{
			myCont = right.myCont;
			myOff = right.myOff;
		}
		return *this; // enables x = y = z, for example
	}

	reference operator*() const
	{
		//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
		size_type block = myCont->getBlock(myOff);
		size_type off = myOff % 4;
		return myCont->map[block][off];
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	DequeConstIterator& operator++() // preincrement
	{
		++myOff;
		return *this;
	}

	DequeConstIterator operator++(int) // postincrement
	{
		DequeConstIterator tmp = *this;
		++* this;
		return tmp;
	}

	DequeConstIterator& operator--() // predecrement
	{
		--myOff;
		return *this;
	}

	DequeConstIterator operator--(int) // postdecrement
	{
		DequeConstIterator tmp = *this;
		--* this;
		return tmp;
	}

	// increment by integer
	DequeConstIterator& operator+=(const difference_type off)
	{
		myOff += off;
		return *this;
	}

	// return this + integer
	DequeConstIterator operator+(const difference_type off) const
	{
		DequeConstIterator tmp = *this;
		return tmp += off;
	}

	// decrement by integer
	DequeConstIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	// return this - integer
	DequeConstIterator operator-(const difference_type off) const
	{
		DequeConstIterator tmp = *this;
		return tmp -= off;
	}

	// return difference of iterators
	difference_type operator-(const DequeConstIterator& right) const
	{
		return (static_cast<difference_type>(this->myOff - right.myOff));
	}

	reference operator[](const difference_type off) const // subscript
	{
		return *(*this + off);
	}

	// test for iterator equality
	bool operator==(const DequeConstIterator& right) const
	{
		return this->myCont == right.myCont && this->myOff == right.myOff;
	}

	// test for iterator inequality
	bool operator!=(const DequeConstIterator& right) const
	{
		return !(*this == right);
	}

	// test if this < right
	bool operator<(const DequeConstIterator& right) const
	{
		return this->myOff < right.myOff;
	}

	// test if this > right
	bool operator>(const DequeConstIterator& right) const
	{
		return right < *this;
	}

	// test if this <= right
	bool operator<=(const DequeConstIterator& right) const
	{
		return !(right < *this);
	}

	// test if this >= right
	bool operator>=(const DequeConstIterator& right) const
	{
		return !(*this < right);
	}

	const MyDeque* myCont; // keep a pointer to deque
	size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
	using size_type = typename MyDeque::size_type;
	using MyBase = DequeConstIterator< MyDeque >;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::pointer;
	using reference = value_type&;

	using MyBase::MyBase;

	DequeIterator() // construct with null deque pointer
	{
	}

	DequeIterator(size_type off, const MyDeque* pDeque)
		: MyBase(off, pDeque) // construct with offset off in *pDeque
	{
	}

	reference operator*() const // return designated object
	{
		return const_cast<reference>(MyBase::operator*());
	}

	pointer operator->() const // return pointer to class object
	{
		return const_cast<pointer>(MyBase::operator->());
		//      return &( operator*() );
	}

	DequeIterator& operator++() // preincrement
	{
		MyBase::operator++();
		return *this;
	}

	DequeIterator operator++(int) // postincrement
	{
		DequeIterator tmp = *this;
		MyBase::operator++();
		return tmp;
	}

	DequeIterator& operator--() // predecrement
	{
		MyBase::operator--();
		return *this;
	}

	DequeIterator operator--(int) // postdecrement
	{
		DequeIterator tmp = *this;
		MyBase::operator--();
		return tmp;
	}

	// increment by integer
	DequeIterator& operator+=(const difference_type off)
	{
		MyBase::operator+=(off);
		return *this;
	}

	// return this + integer
	DequeIterator operator+(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp += off;
	}

	// decrement by integer
	DequeIterator& operator-=(const difference_type off)
	{
		MyBase::operator-=(off);
		return *this;
	}

	using MyBase::operator-; // return difference of iterators

	// return this - integer
	DequeIterator operator-(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp -= off;
	}

	reference operator[](const difference_type off) const // subscript
	{
		return const_cast<reference>(MyBase::operator[](off));
	}
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
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

	DequeVal() // initialize values
		: map(),
		mapSize(0),
		myOff(0),
		mySize(0)
	{
	}

	// determine block from offset
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


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
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

	// construct empty deque
	deque()
		: myData()
	{
	}

	// construct from count * val
	deque(size_type count, const value_type& val)
		: myData()
	{
		myData.map = new value_type * [8]();
		myData.map[0] = new value_type[4];
		myData.map[0][0] = val;
		myData.mapSize = 8;
		myData.mySize = count;
	}

	// construct by copying right
	deque(const deque& right)
		: myData()
	{
		if (right.myData.mySize > 0)
		{
			
			int status = 0;
			myData.mySize = right.myData.mySize;
			myData.myOff = right.myData.myOff;

			if ((right.myData.myOff - 1) % (4 * right.myData.mapSize) % 4 == 3 && right.myData.mySize >= 4 * (right.myData.mapSize - 1))
			{
				myData.mapSize = 2 * right.myData.mapSize;
			}
			else
				myData.mapSize = right.myData.mapSize;

		
			myData.map = new Ty * [myData.mapSize]();
			int size = 0;

			for (size_type i = 0; i < right.myData.mapSize; i++)
			{
				if (right.myData.map[i] != nullptr)
				{
					myData.map[i] = new Ty[4]();
					for (size_type j = 0; j < 4; j++)
					{
						myData.map[i][j] = right.myData.map[i][j];
						size++;
					}
				}
			}
						
			myData.mapSize = 8; //Added 
			while (right.myData.mySize > myData.mapSize * 4 - 4) //Modified
			{
				myData.mapSize *= 2;//Modified
				//status=1; //deleted
			}

			if (status == 1)
				myData.mapSize /= 2;

			while (right.myData.mySize > myData.mapSize * 4 - 4)
			{
				myData.mapSize *= 2;
			}

			if (myData.mapSize == 0)
			{
				myData.mapSize = 8;
			}
			

		}
	}

	// destroy the deque
	~deque()
	{
		clear();
	}

	// return iterator for beginning of mutable sequence
	iterator begin()
	{
		return iterator(myData.myOff, &myData);
	}

	// return iterator for beginning of nonmutable sequence
	const_iterator begin() const
	{
		return const_iterator(myData.myOff, &myData);
	}

	// return iterator for end of mutable sequence
	iterator end()
	{
		return iterator(myData.myOff + myData.mySize, &myData);
	}

	// return iterator for end of nonmutable sequence
	const_iterator end() const
	{
		return const_iterator(myData.myOff + myData.mySize, &myData);
	}

	iterator makeIter(const_iterator where) const
	{
		return iterator(where.myOff, &myData);
	}

	// return length of sequence
	size_type size() const
	{
		return myData.mySize;
	}

	// test if sequence is empty
	bool empty() const
	{
		return myData.mySize == 0;
	}

	// erase element at beginning
	void pop_front()
	{
		size_type front = myData.myOff % (4 * myData.mapSize);
		if (front % 4 == 3)
		{
			size_type back = (myData.myOff + myData.mySize - 1) % (4 * myData.mapSize);
			if (back >= front - 3 && back < front)
			{
				delete[] myData.map[(front - 3) / 4];
				myData.map[(front - 3) / 4] = nullptr;
			}
		}

		--myData.mySize;
		if (myData.mySize == 0)
			myData.myOff = 0;
		else
			++myData.myOff;
	}

	// erase element at end
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

	// insert val at where
	void insert(const_iterator where, const value_type& val)
	{
		size_type off = static_cast<size_type>(where - begin());
		if (myData.mySize == 0)
		{
			if (where == begin() && where == end())
			{

				if (myData.mapSize == 0)
					myData.mapSize = 8;

				myData.map = new Ty * [myData.mapSize]();

				off = (myData.myOff - 1) % (4 * myData.mapSize); //Add 

				myData.map[getBlock(off)] = new Ty[4]();

				myData.map[off / 4][off % 4] = val;

				myData.myOff--; //Add

			}
		}
		else
		{
			if (begin() <= where && where <= end())
			{
				// all elements before where move forward
				if (where <= begin() + myData.mySize / 2)
				{
					size_type newFront = (myData.myOff - 1) % (4 * myData.mapSize);
					if (newFront % 4 == 3 && myData.mySize >= 4 * (myData.mapSize - 1))
					{
						doubleMapSize();
						newFront = (myData.myOff - 1) % (4 * myData.mapSize);
					}

					Ty *temp = new Ty[myData.mySize + 1]();

					iterator it = begin();

					int i = 0;
					for (i = 0; it != begin()+off; it++, i++)
					{
						temp[i] = *it;
					}

					temp[i++] = val;

					for (; it != end(); it++, i++)
					{
						temp[i] = *it;
					}

					myData.myOff--;

					if (myData.myOff % 4 == 3)
						myData.map[getBlock(myData.myOff)] = new Ty[4]();
		
					it = begin();
					i = 0;
					for (;it != end(); it++)
					{
						*it = temp[i++];
					}

					delete [] temp;
				}
				else  // all elements after (and at) where move backward
				{
					size_type newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
					if (newBack % 4 == 0 && myData.mySize >= 4 * (myData.mapSize - 1))
					{
						doubleMapSize();
						newBack = myData.myOff + myData.mySize;
					}

					Ty* temp = new Ty[myData.mySize + 1]();

					iterator it = begin();
					int i = 0;
					for (i = 0; it != begin() + off; it++, i++)
					{
						temp[i] = *it;
					}

					temp[i++] = val;

					for (; it != end(); it++, i++)
					{
						temp[i] = *it;
					}


					if (myData.map[getBlock(newBack)] == nullptr) //Moodify
						myData.map[getBlock(newBack)] = new Ty[4]();//Moodify


					it = begin();
					i = 0;

					for (; it != end() + 1; it++)
					{
						*it = temp[i++];
					}

					delete[] temp;



				}
			}
		}

		myData.mySize++;
		if (myData.myOff >= myData.mapSize * 4) //add
			myData.myOff %= myData.mapSize * 4; //add

	}

	// erase element at where
	void erase(const_iterator where)
	{
		iterator whereIt = makeIter(where);

		if (myData.mySize > 0 && begin() <= whereIt && whereIt < end())
			if (whereIt < begin() + myData.mySize / 2) // all elements before where move backward
			{

				while (whereIt != begin())//Modify
				{
					*whereIt = *(whereIt - 1);
					whereIt--; //Add
				}

				pop_front(); // pop copied element
			}
			else // all elements after where move forward
			{

				while (whereIt+1 != end()) //Modify
				{
					*whereIt = *(whereIt + 1);
					whereIt++; // Add
				}

				pop_back(); // pop copied element
			}
	}

	// erase all
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
			myData.map = nullptr;
		}
	}

private:

	// determine block from offset
	size_type getBlock(size_type off) const
	{
		return myData.getBlock(off);
		//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
	}

	void doubleMapSize()
	{
		if (myData.mapSize > 0)
		{

			size_type newSize = 2 * myData.mapSize;
			MapPtr newMap = new Ty * [newSize]();

			for (size_type i = 0, off = myData.myOff; i < size(); i += 4, off += 4)
			{
				newMap[off % (4 * newSize) / 4] = myData.map[getBlock(off)];
			}

			delete[] myData.map;
			myData.mapSize = newSize;
			myData.map = newMap;

		}
	}

	ScaryVal myData;
};

#endif
