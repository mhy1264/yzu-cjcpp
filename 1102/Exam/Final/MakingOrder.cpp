#include <iostream>
#include <iomanip>
#include "MakingOrder.h" // MakingOrder class definition

extern int inputAnInteger( int begin, int end = INT_MAX );

MakingOrder::MakingOrder( string theEmail, AccountDatabase &theAccountDatabase )
   : email( theEmail ),
     accountDatabase( theAccountDatabase )
{
}

void MakingOrder::run()
{

    Account currentAccount(email);

    currentAccount.setCart(accountDatabase.getCart(email));//Modify

    int userop = 1;
    do
    {

        if (userop==1)
        {
            int itemCode, quant = 0;
            do
            {
                currentAccount.displayCart(); //add
                cout << "Enter foods code  (0 to end): ";
                cin >> itemCode;
            } while (itemCode != 0 and itemCode>=15);

            cin.ignore();
            if (itemCode != 0)
            {
                cout << "\nEnter quantity: ";
                cin >> quant;
                currentAccount.modifyCart(itemCode, quant);
            }
            else
                break;

        }
        if (userop == 2)
        {
            accountDatabase.modifyCart(currentAccount);
            break;
        }
        if (userop == 3)
            break;

        cout << "\n1. Continue Shopping" << endl;
        cout << "\n2. Save Your Shopping Cart" << endl;
        cout << "\n3. Abandon" << endl;
        cout << "\nEnter your choice: (1~3):";
        cin.ignore();
        userop = inputAnInteger(1, 3);
    } while (userop !=-1);
}