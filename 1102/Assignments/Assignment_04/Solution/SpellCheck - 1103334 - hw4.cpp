#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "SpellCheck.h"

SpellCheck::SpellCheck()
   : result()
{
}

void SpellCheck::equalLength( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size();
   vector words;

   findWords( words, dictionary, length );

   string buffer1;
   string buffer2;
   buffer2 = wordToCheck;
   

   for (size_t i = 0; i < words.size(); i++)
   {
       int differNumber = 0;
       buffer1 = words[i];
       for (size_t j = 0; j < length and differNumber<2; j++)
       {
           if (buffer1[j] != buffer2[j])
               differNumber++;
       }

       if (differNumber == 1)
           result.push_back(buffer1);
       buffer1.clear();
   }

   cout << "equal : "<<result.size() << endl;
}

void SpellCheck::shorter( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() + 1;
   vector words;

   findWords( words, dictionary, length );

   string buffer;
   for (size_t i = 0; i < words.size(); i++)
   {
       buffer = words[i];
       for (size_t j = 0; j < length; j++) // ­n®³±¼ªº¦r
       {
           int notSame = 0;
           for (int k = 0, camp = 0; k < length; camp++, k++)
           {
               if (j == camp)
                   camp++;

               if (buffer[camp] != wordToCheck[k])
                   notSame++;
           }

           if (notSame == 0)
           {
               result.push_back(buffer);
               break;
           }
       }
   }
   cout <<"less :"<< result.size() << endl;
}

void SpellCheck::longer( const string &wordToCheck, const vector &dictionary )
{
   size_t length = wordToCheck.size() - 1;
   vector words;

   findWords( words, dictionary, length );

   string buffer;
   for (size_t i = 0; i < words.size(); i++)
   {
       buffer = words[i];
       for (size_t j = 0; j < wordToCheck.size(); j++)
       {
           int notFound = 0;
           for (int k = 0, comp = 0; k < length; k++, comp++)
           {
               if (comp == j)
                   comp++;
               if (buffer[k] != wordToCheck[comp])
                   notFound++;
           }
           if (!notFound)
           {
               result.push_back(buffer);
               break;
           }
       }
   }
  // cout <<"Longer :"<< result.size() << endl;

}

void SpellCheck::findWords( vector &words, const vector &dictionary, size_t length )
{
    for (size_t i = 0; i < dictionary.size(); i++)
        if (dictionary[i].size() == length)
            words.push_back(dictionary[i]);

}

void SpellCheck::output()
{
   cout << "Similar legal words: ";
   cout << result[ 0 ].c_str();
   for( size_t i = 1; i < result.size(); i++ )
      cout << ", " << result[ i ].c_str();
   cout << endl << endl;
}

void SpellCheck::clear()
{
   result.clear();
}