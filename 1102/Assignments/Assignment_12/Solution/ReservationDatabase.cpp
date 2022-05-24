// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

ReservationDatabase::ReservationDatabase()
{
	loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
	saveToReservationFile();
}

void ReservationDatabase::loadReservations()
{

	ifstream inFile("Reservations.dat", ios::in | ios::binary);

	if (!inFile)
	{
		cout << "Reservations.dat cann't be opend";
	}
	Reservation buffer;
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(Reservation)))
	{
		reservations.push_back(buffer);
	}
	inFile.close();

}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

int ReservationDatabase::numReservations( string idNumber )
{

	int num = 0;
	vector< Reservation >::iterator it = reservations.begin();

	for (vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); it++)
	{
		if (it->equalID(idNumber, it->getIDNumber()))
			num++;
	}
	return num;

}

void ReservationDatabase::displayReservations( string idNumber )
{
	cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";

   for( vector< Reservation >::iterator it = reservations.begin(); it < reservations.end(); it++ )
      if( it->equalID( idNumber, it->getIDNumber() ) )
         it->displayReservation();
}

void ReservationDatabase::saveToReservationFile()
{

	ofstream outFile("Reservations.dat", ios::out | ios::binary);
	if (!outFile)
	{
		cout << "Reservations.dat couldn't opened " << endl;
		exit(1);
	}

	int i;

	for (int i = 0; i < reservations.size(); i++)
	{
		Reservation buffer = reservations[i];
		outFile.write(reinterpret_cast<char*>(&buffer), sizeof(Reservation));
	}
	outFile.close();

}