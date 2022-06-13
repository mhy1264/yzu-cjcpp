#include <iostream>
#include <iomanip>
#include "Login.h" // Registration class definition
#include "OrderDatabase.h" // OrderDatabase class definition
#include "MakingOrder.h" // MakingOrder class definition

extern int inputAnInteger(int begin, int end = INT_MAX);
extern Date computeCurrentDate();

Login::Login(AccountDatabase& theAccountDatabase, OrderDatabase& theOrderDatabase)
	: accountDatabase(theAccountDatabase),
	orderDatabase(theOrderDatabase)
{
}

void Login::run()
{
	string email;
	string password;

	cout << "\nEmail (Account number) (0 to end):";
	cin >> email;

	while (!accountDatabase.existAccount(email) and email != "0")
	{
		cout << "\nNo account exists with the e-mail!" << endl;
		cout << "\nEmail (Account number) (0 to end):";
		cin >> email;
		cin.ignore();

	}

	if (email != "0")
	{


		cout << "\nPassword:";
		cin >> password;

		authenticateUser(email, password);

		if (email == "0")
			return;

		MakingOrder makingOrder(email, accountDatabase);

		bool backToTop = false;
		while (!backToTop)
		{
			cout << "\n1. Making order\n"
				<< "2. Display Cart\n"
				<< "3. Proceed to Checkout\n"
				<< "4. Order history\n"
				<< "5. Back to top\n\n";

			int choice;
			do cout << "Enter your choice: (1~5): ";
			while ((choice = inputAnInteger(1, 5)) == -1);

			switch (choice)
			{
			case 1:
				makingOrder.run();
				break;
			case 2:
				displayCart(email);
				break;
			case 3:
				checkout(email);
				break;
			case 4:
				displayOrderHistory(email);
				break;
			case 5:
				backToTop = true; // this session should end
			}
		}
	}
}

void Login::authenticateUser(string& email, string& password)
{

	Account currentAccount(email);
	while (accountDatabase.authenticateUser(email,password))
	{
		cout << "\nInvalid password. Please try again.";

		cout << "\nEmail (Account number) (0 to end):";
		cin >> email;

		if (email == "0")
			return;

		if (!accountDatabase.existAccount(email))
		{
			cout << "\n404 account";
			break;
		}
		cin.ignore();

		cout << "\nPassword:";
		cin >> password;

	}



	cin.ignore();
}

void Login::displayCart(string email)
{
	Account currentAccount(email);

	currentAccount.setCart(accountDatabase.getCart(email));

	currentAccount.displayCart();
}

void Login::checkout(string email)
{
	Account currentAccount(email);

	if (currentAccount.emptyCart())
	{
		cout << "\nYou shopping cart s empty!" << endl;
	}
	else
	{
		Order newOrder;
		cout << "\nOrder Number: " << newOrder.getOrderNumber() << endl;
		cout << "Full Name: " << currentAccount.getName() << endl;
		cout << "Shipping Address" << currentAccount.getAddress() << endl;
		cout << "Bank account: ¦X§@ª÷®w 0062013162077139" << endl;

		newOrder.setDeliveryDate(deliveryDate());
		orderDatabase.pushBack(newOrder);
	}


}

void Login::displayOrderHistory(string email)
{
	if (!orderDatabase.existOrders(email))
	{
		cout << "\nYou have no order history!\n";
		return;
	}

	string name = accountDatabase.getName(email);

	orderDatabase.displayOrders(email, name);
}

Date Login::deliveryDate()
{
	Date date = computeCurrentDate() + 4;
	cout << "\nChoose a delivery date\n";
	for (int i = 1; i <= 28; i++)
	{
		cout << setw(2) << i << ". " << date + i;
		if (i % 4 == 0)
			cout << endl;
		else
			cout << "  ";
	}

	int dateCode;
	do cout << "? ";
	while ((dateCode = inputAnInteger(1, 28)) == -1);

	return date + dateCode;
}