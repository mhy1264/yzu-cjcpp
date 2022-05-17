// BankDatabase.cpp
// Member-function definitions for class BankDatabase.
#include <iostream>
#include "BankDatabase.h" // BankDatabase class definition

// BankDatabase default constructor initializes accounts
// read account informations for all accounts from the binary file "Accounts.dat"
BankDatabase::BankDatabase()
{



}

// write account informations for all accounts to the binary file "Accounts.dat"
BankDatabase::~BankDatabase()
{



}

// retrieve Account object containing specified account number
Account* BankDatabase::getAccount( int accountNumber )
{




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