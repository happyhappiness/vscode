//----------------------------------------------------------------------

std::string cmCTest::MakeXMLSafe(const std::string& str)

{

  std::vector<char> result;

  result.reserve(500);

  const char* pos = str.c_str();

  for ( ;*pos; ++pos)

    {

    char ch = *pos;

    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 && ch != '\r' )

      {

      char buffer[33];

      sprintf(buffer, "&lt;%d&gt;", (int)ch);

      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);

      result.insert(result.end(), buffer, buffer+strlen(buffer));

      }

    else

      {

      const char* const encodedChars[] = {

        "&amp;",

        "&lt;",

        "&gt;"

      };

      switch ( ch )

        {

        case '&':

          result.insert(result.end(), encodedChars[0], encodedChars[0]+5);

          break;

        case '<':

          result.insert(result.end(), encodedChars[1], encodedChars[1]+4);

          break;

        case '>':

          result.insert(result.end(), encodedChars[2], encodedChars[2]+4);

          break;

        case '\n':

          result.push_back('\n');

          break;

        case '\r': break; // Ignore \r

        default:

          result.push_back(ch);

        }

      }

    }

  return std::string(&*result.begin(), result.size());

}



//----------------------------------------------------------------------

