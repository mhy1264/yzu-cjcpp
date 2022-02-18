#include <iostream>
#include <cstring>
using namespace std;

// product = multiplicand * multiplier
void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandSize, int multiplierSize, int& productSize);

int main()
{
    char strX[251];
    char strY[251];

    while (cin >> strX >> strY)
    {
        int multiplicand[250] = {};
        int multiplicandSize = strlen(strX);
        for (int i = 0; i < multiplicandSize; i++)
            multiplicand[multiplicandSize - i - 1] = strX[i] - '0';

        int multiplier[250] = {};
        int multiplierSize = strlen(strY);
        for (int i = 0; i < multiplierSize; i++)
            multiplier[multiplierSize - i - 1] = strY[i] - '0';

        int product[500] = {};
        int productSize = multiplicandSize + multiplierSize;

        multiplication(multiplicand, multiplier, product, multiplicandSize, multiplierSize, productSize);

        for (int i = productSize - 1; i >= 0; i--)
            cout << product[i];
        cout << endl;
    }

    return 0;
}

void multiplication(int multiplicand[], int multiplier[], int product[],
    int multiplicandSize, int multiplierSize, int& productSize)
{
    int i, j, startPosit = 0, cnt = 0;
    for (i = 0; i < multiplicandSize; i++)
    {
        for (j = 0; j < multiplierSize; j++)
        {
            product[startPosit + cnt] += multiplicand[i] * multiplier[j];
            if (product[startPosit + cnt] >= 10)
            {
                product[startPosit + cnt + 1] += product[startPosit + cnt] / 10;
                product[startPosit + cnt] %= 10;
            }
            cnt++;
        }
        startPosit++;
        cnt = 0;
    }

    for (i = productSize; i > 0; i--)
        if (product[i - 1] != 0)
            break;
    productSize = i;
    if (productSize == 0)
        productSize = 1;
}