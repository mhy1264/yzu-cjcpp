// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition

extern bool leapYear(int year);
extern Date computeCurrentDate();

MakeReservation::MakeReservation(ReservationDatabase& theReservationDatabase,
	AvailRoomDatabase& theAvailableRoomsDatabase)
	: reservationDatabase(theReservationDatabase),
	availableRoomDatabase(theAvailableRoomsDatabase)
{
}

void MakeReservation::execute()
{
	Date currentDate = computeCurrentDate();

	Date availableMonths[7];

	computeAvailableMonths(currentDate, availableMonths);

	int checkInYMCode;
	int firstDay;
	int lastDay;

	Date checkInDate;
	Date checkOutDate;

	inputCheckInDates(checkInDate, currentDate, availableMonths, checkInYMCode, firstDay, lastDay);
	inputCheckOutDates(checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay);

	cout << "\nCheck in date: " << checkInDate.getYear() << '-'
		<< setw(2) << setfill('0') << checkInDate.getMonth() << '-'
		<< setw(2) << checkInDate.getDay() << endl;

	cout << "Check out date: " << checkOutDate.getYear() << '-'
		<< setw(2) << checkOutDate.getMonth() << '-'
		<< setw(2) << checkOutDate.getDay() << endl;




	availableRoomDatabase.displayAvailableRooms(checkInDate, checkOutDate);

	const char roomTypeName[6][20] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
											   "Superior Suite", "Deluxe Suite" };

	int roomType = 0, numRooms = 0,min=0;
	cout << "\nRoomType: " << endl;
	for (int i = 0; i < 6; i++)
	{
		min = availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate);
		if (min)
			cout << i << " " << roomTypeName[i] << endl;
		
	}
	cout << "6. Give Up" << endl;

	do
	{
		cout << "? ";
		cin >> roomType;
		min = availableRoomDatabase.compMinNumRooms(roomType, checkInDate, checkOutDate);
	} while (!(min or roomType==6));
	
	if (roomType != 6)
	{
		do
		{
			cout << "Number of rooms( " << min << " rooms available) : ";
			cin >> numRooms;
		} while (!(numRooms and numRooms <= min));

		availableRoomDatabase.decreaseAvailRooms(roomType, numRooms, checkInDate, checkOutDate);

		cout << "\nID Number: ";
		string idNumber;
		cin >> idNumber;

		cout << "\nName: ";
		string name;
		cin >> name;

		cout << "\nMobile Phone: ";
		string mobile;
		cin >> mobile;
		cin.ignore();

		newReservation.setReservation(roomType, numRooms, checkInDate, checkOutDate, idNumber, name, mobile);

		cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
		newReservation.displayReservation();

		reservationDatabase.pushBack(newReservation);

		cout << "\nReservation successfully!" << endl;
	}

}

void MakeReservation::computeAvailableMonths(Date currentDate, Date availableMonths[])
{

	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	for (int k = 1; k < 7; k++)
	{
		int tempMonth = currentDate.getMonth() + k - 1;
		int tempYear = currentDate.getYear();
		if (tempMonth > 12)
		{
			tempMonth %= 12;
			tempYear++;
		}
		availableMonths[k].setYear(tempYear);
		availableMonths[k].setMonth(tempMonth);
		availableMonths[k].setDay(1);
	}

	if (currentDate.getDay() == days[currentDate.getMonth()])
		availableMonths[1].setDay(0);

}


void MakeReservation::inputCheckInDates(Date& checkInDate, Date currentDate,
	Date availableMonths[], int& checkInYMCode, int& firstDay, int& lastDay)
{

	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	cout << "Please Input Check In Date" << endl;

	cout << "Month¡G" << endl;

	for (int i = 1; i < 7; i++)
		if (availableMonths[i].getDay())
			cout << i << " " << availableMonths[i].getYear() << " " << availableMonths[i].getMonth() << endl;

	do
	{
		cout << "? ";
		cin >> checkInYMCode;
	} while (!(checkInYMCode > 0 and checkInYMCode < 7 and availableMonths[checkInYMCode].getDay()));

	if (leapYear(availableMonths[checkInYMCode].getMonth()))
		days[2] = 29;

	int day = 0;

	firstDay = (availableMonths[checkInYMCode].getMonth() == currentDate.getMonth()) ? currentDate.getDay() : 1;
	lastDay = days[availableMonths[checkInYMCode].getMonth()];
	do
	{
		cout << "Day (" << firstDay << " ~ " << lastDay << ")¡G";
		cin >> day;
	} while (!(day >= firstDay and day <= lastDay));

	checkInDate.setYear(availableMonths[checkInYMCode].getYear());
	checkInDate.setMonth(availableMonths[checkInYMCode].getMonth());
	checkInDate.setDay(day);

	if (day == days[availableMonths[checkInYMCode].getMonth()])
		checkInYMCode++;

}

void MakeReservation::inputCheckOutDates(Date& checkOutDate, Date checkInDate,
	Date availableMonths[], int checkInYMCode, int firstDay, int lastDay)
{
	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	cout << "\nPlease Input Check Out Date" << endl;
	cout << "\nMonth¡G" << endl;

	for (int i = checkInYMCode; i < 7; i++)
		if (availableMonths[i].getDay())
			cout << i << " " << availableMonths[i].getYear() << " " << availableMonths[i].getMonth() << endl;
	int month;
	do
	{
		cout << "? ";
		cin >> month;
	} while (!(month > 0 and month < 7 and availableMonths[month].getDay()));

	if (leapYear(availableMonths[checkInYMCode].getMonth()))
		days[2] = 29;

	int day = 0;

	firstDay = availableMonths[month].getMonth() == checkInDate.getMonth() ? checkInDate.getDay() + 1 : 1;
	lastDay = days[availableMonths[month].getMonth()];

	do
	{
		cout << "Day (" << firstDay << " ~ " << lastDay << ")¡G";
		cin >> day;
	} while (!(day >= firstDay and day <= lastDay));

	checkOutDate.setYear(availableMonths[month].getYear());
	checkOutDate.setMonth(availableMonths[month].getMonth());
	checkOutDate.setDay(day);
}