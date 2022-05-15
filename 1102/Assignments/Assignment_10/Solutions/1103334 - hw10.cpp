#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

class USER
{
public:
	USER(int I, string A, string P, double AV, double T)
	{
		account = A;
		pin = P;
		avail = AV;
		total = T;
		userId = I;
	}

	void showBalance()
	{
		cout << endl;
		cout << "Balance Information:" << endl;
		cout << " - Available balance : " << avail << endl;
		cout << " - Total balance : " << total << endl;
		cout << endl;

	}

	int withdraw(int remainingBills)
	{
		int option;
		int bill[] = { 0,20,40,60,100,200,0 };
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
			return -1;
		}
		else if (option == 6)
		{
			cout << "Canceling transaction..." << endl << endl;
			return option;
		}
		else if (remainingBills < bill[option] / 20)
		{
			cout << "Insufficient funds in ATM" << endl;
			cout << "Please choose a smaller amount" << endl;
			return -1;
		}
		else if (avail < bill[option])
		{
			cout << "Insufficient funds in your account." << endl;
			cout << "Please choose a smaller amount" << endl;
			return -1;
		}
		else
		{
			remainingBills -= bill[option] / 20;
			avail -= bill[option];
			total -= bill[option];
			cout << "Please take your cash from the cash dispenser" << endl << endl;
			return option;
		}

	}

	void des()
	{
		cout << endl;
		int cent;
		cout << "Please enter a deposit amount in CENTS(or 0 to cancel) : ";
		cin >> cent;
		if(cent)
		{
			cout << endl;
			cout << "Please insert a deposit envelope containing $" << cent / 100 << " in the deposit slot." << endl;

			cout << "Your envelope has been received." << endl;
			cout << "NOTE : The money deposited will not be available until we" << endl;
			cout << "verify the amount of any enclosed cash, and any enclosed checks clear." << endl;
			total += cent / 100;
		}

	}

	string getAcc()
	{
		return account;
	}
	
	string getPin()
	{
		return pin;
	}

	USER operator=(USER right)
	{
		userId = right.userId;
		account = right.account;
		pin = right.pin;
		avail = right.avail;
		total = right.total;
		return *this;
	}

private:
	int userId;
	string account;
	string pin;
	double avail;
	double total;
};

class ATM
{
public:
	ATM()
	{
		availMoney = 500;
	}

	int login(vector<USER>user,int num)
	{
		
		cout << "Welcome" << endl << endl;;
		string acc, pin;
		cout << "Please enter your account number : ";
		cin >> acc;
		cout << endl;
		cout << "Enter your PIN : ";
		cin >> pin;


		for (int i = 0; i < num; i++)
			if (acc == user[i].getAcc() and pin == user[i].getPin())
				return i;

		return -1;
	}

	void show()
	{
		cout << endl;
		cout << "Main menu :" << endl;
		cout << "1 - View my balance" << endl;
		cout << "2 - Withdraw cash" << endl;
		cout << "3 - Deposit funds" << endl;
		cout << "4 - Exit" << endl;

	}

	int remainingBills()
	{
		return availMoney;
	}

	void minus(int n)
	{
		int cash[] = { 0,1,2,3,5,10,0 };
		availMoney -= cash[n];
	}

private:
	int availMoney;
};

int main()
{
	int op;
	ATM atm;
	USER user1(1, "12345", "54321", 1000, 1200);
	USER user2(2, "98765", "56789", 200, 200);
	vector <USER>user;
	user.push_back(user1);
	user.push_back(user2);

	USER currentUser(0, " ", " ", 0, 0);
	int currentId = 0;
	int status = 0;

	while (1)
	{
		currentId = atm.login(user,2);
		if (currentId != -1 )
		{
			currentUser = user[currentId];
			do
			{
				
				atm.show();
				cout << "Enter a choice : ";
				cin >> op;
				switch (op)
				{
				case 1:
					currentUser.showBalance();
					break;

				case 2:
					do 
					{
						status = currentUser.withdraw(atm.remainingBills());
					}while(status == -1);

					atm.minus(status);

					break;
				case 3:
					currentUser.des();
					break;

				case 4:
					cout << endl;
					cout << "Exiting the system..." << endl << endl;;

					cout <<"Thank you! Goodbye!"<<endl<<endl;
					user[currentId] = currentUser;
					break;

				default:
					cout << "You did not enter a valid selection. Try again." << endl;
					break;
				}
			} while (op != 4);
		}
		else
		{
			cout << endl;
			cout << "Invalid account number or PIN. Please try again." << endl << endl;;
		}

	}

}
