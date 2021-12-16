#include <iostream>
#include <fstream>
#include<iomanip>
using namespace std;

struct Account
{
	int accountNumber;    // account number-
	int pin;              // personal identification number
	int availableBalance; // funds available for withdrawal
	int totalBalance;     // funds available + funds waiting to clear
};

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number (in Accounts.dat) of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount(int accountNumber, int pin, Account& currentAccount, int& recordNumber);

// display the main menu and perform transactions
void performTransactions(Account& currentAccount, int& recordNumber, int& remainingBills);

// perform withdrawal transaction
void withdrawal(Account& currentAccount, int& remainingBills);

// perform deposit transaction
void deposit(Account& currentAccount);

// write currentAccount into the n-th record of Accounts.dat
void saveAccount(Account currentAccount, int n);

const int INITIAL_BILLS = 5; // the number bills loaded each day

int main()
{
	// the number of remaining bills in the cash dispenser
	int remainingBills = INITIAL_BILLS;
	int recordNumber;
	Account currentAccount;

	// welcome and authenticate user; perform transactions
	while (true)
	{
		int accountNumber;
		int pin;

		do
		{
			cout << "Welcome!\n";
			cout << "\nPlease enter your account number: ";
			cin >> accountNumber;
			cout << "\nEnter your PIN: ";
			cin >> pin; // input PIN
		} while (!loadAccount(accountNumber, pin, currentAccount, recordNumber));

		performTransactions(currentAccount, recordNumber, remainingBills);
	}
} // end function main

bool loadAccount(int accountNumber, int pin, Account& currentAccount, int& recordNumber)
{
	ifstream inFile("Accounts.dat", ios::in | ios::binary);;
	if (!inFile)
	{
		cout << "Account.dat couldn't be opened!" << endl;
		exit(1);
	}

	Account buffer;
	recordNumber = 0;
	while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(Account)))
	{
		recordNumber++;
		if (buffer.accountNumber == accountNumber and buffer.pin == pin)
		{
			currentAccount.accountNumber = buffer.accountNumber;
			currentAccount.pin = buffer.pin;
			currentAccount.availableBalance = buffer.availableBalance;
			currentAccount.totalBalance = buffer.totalBalance;
			return 1;
		}
	}
	cout << "Invalid account number or PIN. Please try again." << endl << endl;
	return 0;
	inFile.close();

} // end function loadAccount


// display the main menu and perform transactions
void performTransactions(Account& currentAccount, int& recordNumber, int& remainingBills)
{
	int options;

	do
	{
		cout << "Main menu : " << endl;// displayed in performTransactions
		cout << "    1 - View my balance" << endl;
		cout << "    2 - Withdraw cash" << endl;
		cout << "    3 - Deposit funds" << endl;
		cout << "    4 - Exit" << endl;

		cout << "Enter a choice : ";
		cin >> options;
		switch (options)
		{
		case 1:
			cout << endl;
			cout << "Balance Information:" << endl;
			cout << " - Available balance : " << currentAccount.availableBalance << endl;
			cout << " - Total balance : " << currentAccount.totalBalance << endl;
			cout << endl;
			//performTransactions(currentAccount, recordNumber, remainingBills);
			break;
		case 2:
			withdrawal(currentAccount, remainingBills);
			break;
		case 3:
			deposit(currentAccount);
			break;
		case 4:  //exit 
			cout << endl;
			cout << "Exiting the system..." << endl;
			cout << "Thank you!Goodbye!" << endl;
			saveAccount(currentAccount, recordNumber);
			return; 
		default:
			cout << "You did not enter a valid selection. Try again." << endl;
			cout << endl;
			return performTransactions(currentAccount, recordNumber, remainingBills);
			break;
		}
	} while (options != 4);


} // end function performTransactions

// perform withdrawal transaction
void withdrawal(Account& currentAccount, int& remainingBills)
{
	int option;
	int bill[] = { 0,20,40,60,100,200 };
	cout << endl;
	cout << "1 - $20 " << "  " << "2 - $40" << endl << endl;;
	cout << "3 - $60 " << "  " << "4 - $100" << endl << endl;
	cout << "5 - $200" << "  " << "6 - Cancel transaction" << endl << endl;
	cout << "Withdrawal options:";
	cin >> option;
	cout << endl;
	if (option > 6)
	{
		cout << "Invalid selection. Try again." << endl;
		withdrawal(currentAccount, remainingBills);
	}
	else if (option == 6)
	{
		cout << "Canceling transaction..." << endl << endl;
	}
	else if (remainingBills < bill[option] / 20)
	{
		cout << "Insufficient funds in ATM" << endl;
		cout << "Please choose a smaller amount" << endl;
		withdrawal(currentAccount, remainingBills);
	}
	else if (currentAccount.availableBalance < bill[option])
	{
		cout << "Insufficient funds in your account." << endl;
		cout << "Please choose a smaller amount" << endl;
		withdrawal(currentAccount, remainingBills);
	}
	else
	{
		remainingBills -= bill[option] / 20;
		currentAccount.availableBalance -= bill[option];
		cout << "Please take your cash from the cash dispenser" << endl << endl;
		//		cout << "avaliable Balance " << currentAccount.availableBalance << " ATM remaining Bill " << remainingBills << endl << endl;
	}
} // end function withdrawal

// perform deposit transaction
void deposit(Account& currentAccount)
{
	cout << "\nPlease enter a deposit amount in dollars (or 0 to cancel): ";
	int amount;
	cin >> amount; // receive input of deposit amount

	// check whether user entered a deposit amount or canceled
	if (amount == 6)
		cout << "\nCanceling transaction...\n";
	else // user canceled instead of entering amount
	{
		// request deposit envelope containing specified amount
		cout << "\nPlease insert a deposit envelope containing ";
		cout << "$" << amount;
		cout << " in the deposit slot.\n";

		cout << "\nYour envelope has been received."
			<< "\nNOTE: The money deposited will not be available until we"
			<< "\nverify the amount of any enclosed cash, and any enclosed checks clear.\n\n";

		// credit account to reflect the deposit
		currentAccount.totalBalance += amount; // add to total balance
	}                                         // end if
} // end function deposit

void saveAccount(Account currentAccount, int n)
{
	fstream outFile("Accounts.dat", ios::out | ios::in | ios::binary);

	if (!outFile)
	{
		cout << "Accounts.bat cann't be opened! " << endl;
		exit(1);
	}

	int location = (n - 1) * sizeof(Account);
	outFile.seekp(location, outFile.beg);
	outFile.write(reinterpret_cast<const char*>(&currentAccount), sizeof(Account));

	//
	//outFile.seekp(8 + 16 * (n - 1), ios::beg);
	//outFile.write(reinterpret_cast<char*>(&currentAccount.availableBalance), sizeof(currentAccount.availableBalance));
	//outFile.write(reinterpret_cast<char*>(&currentAccount.totalBalance), sizeof(currentAccount.totalBalance));


	outFile.close();
}