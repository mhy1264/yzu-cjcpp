#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;


}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   if( count > 15 )
   {
      myRes = ( mySize / 16 ) * 16 + 15;


   }


}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = right.mySize;
   myRes = ( mySize / 16 ) * 16 + 15;


}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right )
{
   if( this != &right )
   {
      if( right.mySize > myRes )
      {


         myRes = myRes * 3 / 2;
         if( myRes < ( right.mySize / 16 ) * 16 + 15 )
            myRes = ( right.mySize / 16 ) * 16 + 15;


      }


   }

   return *this;
}

bool string::equal( const string &right )
{


}

string& string::erase( const size_type off, size_type count )
{
   if( off < mySize )
   {


   }

   return *this;
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

void string::push_back( char ch )
{
   resize( mySize + 1 );
   myPtr()[ mySize - 1 ] = ch;
}

void string::pop_back()
{
   if( mySize > 0 )
      --mySize;
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

void string::resize( const size_type newSize, const char ch )
{
   // determine new length, padding with ch elements as needed
   if( newSize > mySize )
   {
      if( newSize > myRes )
      {
         size_type newMyRes = myRes * 3 / 2;
         if( newMyRes < ( newSize / 16 ) * 16 + 15 )
            newMyRes = ( newSize / 16 ) * 16 + 15;


      }


   }


}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
} 

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head><meta http-equiv="Content-Type" content="text/html; charset=utf-8" /><title>

</title></head>
<body>
    <form method="post" action="./DownloadFile.aspx?Source=Course&amp;CourseType=1&amp;AttachmentID=92588&amp;AttachmentFileName=string+-+Student+ID+-+hw2.cpp" id="form1">
<div class="aspNetHidden">
<input type="hidden" name="__VIEWSTATE" id="__VIEWSTATE" value="/wEPDwUKLTEzNDM3NzkxOWRkE99b+haQV3ZBm26TDQfyZY8BZWY=" />
</div>

<div class="aspNetHidden">

	<input type="hidden" name="__VIEWSTATEGENERATOR" id="__VIEWSTATEGENERATOR" value="F69017DB" />
</div>
    <div>
    
    </div>
    </form>
</body>
</html>
