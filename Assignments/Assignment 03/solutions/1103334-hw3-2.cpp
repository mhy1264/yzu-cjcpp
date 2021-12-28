#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cstring>
using std::memset;

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2);

// difference = minuend - subtrahend provided that minuend > subtrahend
void subtraction(int minuend[], int subtrahend[], int difference[],
    int minuendSize, int subtrahendSize, int& differenceSize);


char strA[10000], strB[10000];
int numA[10000], numB[10000], numC[10000];

int main()
{
    int n;
    while (cin >> n)
        for (int k = 0; k < n; ++k)
        {
            cin >> strA >> strB;
            memset(numA, 0, sizeof(numA));
            memset(numB, 0, sizeof(numB));
            memset(numC, 0, sizeof(numC));

            int sizeA = strlen(strA);
            for (int i = 0; i < sizeA; ++i)
                numA[i] = strA[sizeA - 1 - i] - '0';

            int sizeB = strlen(strB);
            for (int i = 0; i < sizeB; ++i)
                numB[i] = strB[sizeB - 1 - i] - '0';

            int sizeC = 0;
            if (less(numA, numB, sizeA, sizeB))
            {
                cout << "-";
                subtraction(numB, numA, numC, sizeB, sizeA, sizeC);
            }
            else if (less(numB, numA, sizeB, sizeA))
                subtraction(numA, numB, numC, sizeA, sizeB, sizeC);
            else
            {
                sizeC = 1;
                numC[0] = 0;
            }

            for (int i = sizeC - 1; i >= 0; i--)
                cout << numC[i];
            cout << endl;
        }

    return 0;
}

bool less(int hugeInt1[], int hugeInt2[], int size1, int size2)
{
    int i;
    int check;
    if (size1 < size2)
    {
        check = 1;
    }
    else if (size1 > size2)
    {
        check = 0;
    }
    else
    {
        check = 0;
        for (int i = size1 - 1; i >= 0; i--)
        {
            if (hugeInt1[i] == hugeInt2[i])
            {
                continue;
            }
            else
            {
                if (hugeInt1[i] < hugeInt2[i])
                    check = 1;
                else
                    check = 0;
                break;
            }

        }

    }

    return check;

}

// difference = minuend - subtrahend provided that minuend > subtrahend
void subtraction(int minuend[], int subtrahend[], int difference[],
    int minuendSize, int subtrahendSize, int& differenceSize)
{
    int i;

    for (i = 0; i < subtrahendSize; i++)
    {
        difference[i] = minuend[i] - subtrahend[i];
    }
    for (i = subtrahendSize; i < minuendSize; i++)
    {
        difference[i] = minuend[i];
    }
    int check = 1;
    while (check)
    {
        check = 0;
        for (i = 0; i < minuendSize; i++)
        {
            if (difference[i] < 0)
            {
                difference[i] += 10;
                difference[i + 1] -= 1;
            }
        }

        for (i = 0; i < minuendSize and check; i++)
            if (difference[i] < 0)
                check = 1;
    }

    for (i = minuendSize; i > 0; i--)
    {
        if (difference[i - 1] != 0)
            break;
    }
    differenceSize = i;
}
