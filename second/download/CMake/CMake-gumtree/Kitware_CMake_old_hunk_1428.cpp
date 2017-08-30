}



//----------------------------------------------------------------------------

void Glob::Escape(int ch, char* buffer)

{

  if (! (

      'a' <= ch && ch <= 'z' ||

      'A' <= ch && ch <= 'Z' ||

      '0' <= ch && ch <= '9') )

    {

    sprintf(buffer, "\\%c", ch);

    }

  else

    {

#if defined( KWSYS_GLOB_CASE_INDEPENDENT )

    // On Windows and apple, no difference between lower and upper case

    sprintf(buffer, "%c", tolower(ch));

#else

    sprintf(buffer, "%c", ch);

#endif

    }

}



//----------------------------------------------------------------------------

kwsys_stl::vector<kwsys_stl::string>& Glob::GetFiles()

{

  return this->Internals->Files;

}



//----------------------------------------------------------------------------

kwsys_stl::string Glob::ConvertExpression(const kwsys_stl::string& expr)

{



  kwsys_stl::string::size_type i = 0;

  kwsys_stl::string::size_type n = expr.size();



  kwsys_stl::string res = "^";

  kwsys_stl::string stuff = "";



  while ( i < n )

    {

    int c = expr[i];

    i = i+1;

    if ( c == '*' )

      {

      res = res + ".*";

      }

    else if ( c == '?' )

      {

      res = res + ".";

      }

    else if ( c == '[' )

      {

      kwsys_stl::string::size_type j = i;

      if ( j < n && ( expr[j] == '!' || expr[j] == '^' ) )

        {

        j = j+1;

        }

      if ( j < n && expr[j] == ']' )

        {

        j = j+1;

        }

      while ( j < n && expr[j] != ']' )

        {

        j = j+1;

        }

      if ( j >= n )

        {

        res = res + "\\[";

        }

      else

        {

        stuff = "";

        kwsys_stl::string::size_type cc;

        for ( cc = i; cc < j; cc ++ )

          {

          if ( expr[cc] == '\\' )

            {

            stuff += "\\\\";

            }

          else

            {

            stuff += expr[cc];

            }

          }

        i = j+1;

        if ( stuff[0] == '!' || stuff[0] == '^' )

          {

          stuff = '^' + stuff.substr(1);

          }

        else if ( stuff[0] == '^' )

          {

          stuff = '\\' + stuff;

          }

        res = res + "[" + stuff + "]";

        }

      }

    else

      {

      char buffer[100];

      buffer[0] = 0;

      this->Escape(c, buffer);

      res = res + buffer;

      }

    }

  return res + "$";

}



//----------------------------------------------------------------------------

