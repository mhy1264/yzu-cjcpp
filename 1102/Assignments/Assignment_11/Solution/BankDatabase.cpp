// BankDatabase.cpp
// Member-function definitions for class BankDatabase.
#include <iostream>
#include "BankDatabase.h" // BankDatabase class definition

// BankDatabase default constructor initializes accounts
// read account informations for all accounts from the binary file "Accounts.dat"
BankDatabase::BankDatabase()
{

	ifstream inFile("Accounts.dat", ios::in | ios::binary);;
	if (!inFile)
	{
		cout << "Account.dat couldn't be opened!" << endl;
		exit(1);
	}

	Account buffer;

	while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(Account)))
	{
		accounts.push_back(buffer);
	}
	inFile.close();

}

// write account informations for all accounts to the binary file "Accounts.dat"
BankDatabase::~BankDatabase()
{
	fstream outFile("Accounts.dat", ios::out | ios::in | ios::binary);

	if (!outFile)
	{
		cout << "Accounts.bat cann't be opened! " << endl;
		exit(1);
	}

	int location = 0;
	outFile.seekp(location, outFile.beg);
	for (int i = 0; i < accounts.size(); i++)
	{
		outFile.write(reinterpret_cast<const char*>(&accounts[i]), sizeof(Account));
	}


}

// retrieve Account object containing specified account number
Account* BankDatabase::getAccount( int accountNumber )
{

	for (int i = 0; i < accounts.size(); i++)
		if (accounts[i].getAccountNumber() == accountNumber)
			return &accounts[i];

   return nullptr; // if no matching account was found, return nullptr
}

// determine whether user-specified account number and PIN match
// those of an account in the database
bool BankDatabase::authenticateUser( int userAccountNumber, int userPIN )
{
   // attempt to retrieve the account with the account number
   Account * const userAccountPtr = getAccount( userAccountNumber );

   // if account exists, return result of Account function validatePIN
   if ( userAccountPtr != nullptr )
      return userAccountPtr->validatePIN( userPIN );
   else
      return false; // account number not found, so return false
}

// return available balance of Account with specified account number
double BankDatabase::getAvailableBalance( int userAccountNumber )
{
   Account * const userAccountPtr = getAccount( userAccountNumber );
   return userAccountPtr->getAvailableBalance();
}

// return total balance of Account with specified account number
double BankDatabase::getTotalBalance( int userAccountNumber )
{
   Account * const userAccountPtr = getAccount( userAccountNumber );
   return userAccountPtr->getTotalBalance();
}

// credit an amount to Account with specified account number
void BankDatabase::credit( int userAccountNumber, double amount )
{
   Account * const userAccountPtr = getAccount( userAccountNumber );
   userAccountPtr->credit( amount );
}

// debit an amount from Account with specified account number
void BankDatabase::debit( int userAccountNumber, double amount )
{
   Account * const userAccountPtr = getAccount( userAccountNumber );
   userAccountPtr->debit( amount );
}