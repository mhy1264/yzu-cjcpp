// AvailRoomDatabase.cpp
// Member-function definitions for class AvailRoomDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

extern bool leapYear(int year);
extern Date computeCurrentDate();
//char availFileName[] = "Available Rooms 2021-11-24.dat";
//char availFileName[] = "Available Rooms 2022-2-22.dat";
char availFileName[] = "Available Rooms 2022-5-23.dat";
//char availFileName[] = "Available Rooms 2022-5-28.dat";
//char availFileName[] = "Available Rooms blank.dat";

AvailRoomDatabase::AvailRoomDatabase()
{
	loadAvailableRooms();

	if (availRooms.size() == 0)
		initAvailRooms(); // create available rooms information for 6 months
	else
		appendAvailRooms(); // append new available rooms information
}

AvailRoomDatabase::~AvailRoomDatabase()
{
	saveAvailableRooms();
}

void AvailRoomDatabase::loadAvailableRooms()
{

	ifstream inFile(availFileName, ios::in | ios::binary);
	AvailRoom buffer;
	Date today = computeCurrentDate();

	if (!inFile)
	{
		cout << "Avaliable couldn't be opened";
	}
	while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(AvailRoom)))
	{
		if (buffer.getDate() >= today)
		{
			availRooms.push_back(buffer);
		}
	}
	inFile.close();

}

void AvailRoomDatabase::initAvailRooms()
{

	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	Date current = computeCurrentDate();

	Date deadLine;
	deadLine.setMonth((current.getMonth() + 6) % 12);
	deadLine.setYear(current.getYear() + (current.getMonth() + 6) / 12);

	if (leapYear(deadLine.getYear()))
		days[2] = 29;

	deadLine.setDay(days[deadLine.getMonth()]);

	while (current <= deadLine)
	{
		AvailRoom temp;
		temp.setDate(current.getYear(), current.getMonth(), current.getDay());
		temp.initAvailRooms();
		availRooms.push_back(temp);
		++current;

	}
}

void AvailRoomDatabase::appendAvailRooms()
{

	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	Date least = availRooms[availRooms.size() - 1].getDate();

	Date current;
	current.setDay(least.getDay());
	current.setMonth(least.getMonth());
	current.setYear(least.getYear());

	Date today = computeCurrentDate();

	Date deadLine;
	deadLine.setMonth((today.getMonth() + 6) % 12);
	deadLine.setYear(today.getYear() + (today.getMonth() + 6) / 12);

	if (leapYear(deadLine.getYear()))
		days[2] = 29;

	deadLine.setDay(days[deadLine.getMonth()]);

	while (current <= deadLine)
	{
		AvailRoom temp;
		temp.setDate(current.getYear(), current.getMonth(), current.getDay());
		temp.initAvailRooms();
		availRooms.push_back(temp);
		
		++current;

	}
	//cout << " " << endl;
}

void AvailRoomDatabase::displayAvailableRooms(Date checkInDate, Date checkOutDate)
{
	cout << "\nThe number of available rooms of each room type:\n\n";
	cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

	vector< AvailRoom >::iterator checkInIterator;
	vector< AvailRoom >::iterator checkOutIterator;

	findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);

	for (vector< AvailRoom >::iterator it = checkInIterator; it < checkOutIterator; ++it)
		cout << it->getDate().getYear() << "-"
		<< setw(2) << setfill('0') << it->getDate().getMonth() << "-"
		<< setw(2) << it->getDate().getDay()
		<< setw(16) << setfill(' ') << it->getAvailRoom(1)
		<< setw(14) << it->getAvailRoom(2)
		<< setw(19) << it->getAvailRoom(3)
		<< setw(17) << it->getAvailRoom(4)
		<< setw(15) << it->getAvailRoom(5) << "\n";
}

int AvailRoomDatabase::compMinNumRooms(int roomType,
	const Date& checkInDate, const Date& checkOutDate)
{
	vector< AvailRoom >::iterator checkInIterator;
	vector< AvailRoom >::iterator checkOutIterator;

	findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);

	int min = 100;
	for (vector< AvailRoom >::iterator it = checkInIterator; it != checkOutIterator; it++)
	{
		if (it->getAvailRoom(roomType) < min)
			min = it->getAvailRoom(roomType);
	}

	return min;

}

void AvailRoomDatabase::decreaseAvailRooms(int roomType, int numRooms,
	const Date& checkInDate, const Date& checkOutDate)
{

	vector< AvailRoom >::iterator checkInIterator;
	vector< AvailRoom >::iterator checkOutIterator;

	findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);
	vector< AvailRoom >::iterator it = checkInIterator;

	for (it = checkInIterator; it != checkOutIterator; it++)
	{
		it->decreaseAvailRooms(roomType, numRooms);
	}

}

void AvailRoomDatabase::saveAvailableRooms()
{

	ofstream outFile(availFileName, ios::out | ios::binary);
	if (!outFile)
	{
		cout << "File \" Reservation.bat\" couldn't be opened" << endl;
	}

	for (vector <AvailRoom>::iterator it = availRooms.begin(); it != availRooms.end(); it++)
	{
		AvailRoom temp = *it;
		outFile.write(reinterpret_cast<char*>(&temp), sizeof(AvailRoom));
	}

}

void AvailRoomDatabase::findIterators(const Date& checkInDate, const Date& checkOutDate,
	vector< AvailRoom >::iterator& checkInIterator,
	vector< AvailRoom >::iterator& checkOutIterator)
{

	for (vector <AvailRoom>::iterator it = availRooms.begin(); it != availRooms.end(); it++)
	{
		if (it->getDate() == checkInDate)
			checkInIterator = it;
		if (it->getDate() == checkOutDate)
		{
			checkOutIterator = it;
			break;
		}
	}

}