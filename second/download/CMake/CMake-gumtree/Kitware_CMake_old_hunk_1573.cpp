//----------------------------------------------------------------------
std::string cmCTest::MakeXMLSafe(const std::string& str)
{
  cmOStringStream ost;
  // By uncommenting the lcnt code, it will put newline every 120 characters
  //int lcnt = 0;
  for (std::string::size_type  pos = 0; pos < str.size(); pos ++ )
    {
    unsigned char ch = str[pos];
    if ( ch == '\r' )
      {
      // Ignore extra CR characters.
      }
    else if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 )
      {
      char buffer[33];
      sprintf(buffer, "&lt;%d&gt;", (int)ch);
      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
      ost << buffer;
      //lcnt += 4;
      }
    else
      {
      switch ( ch )
        {
        case '&': ost << "&amp;"; break;
        case '<': ost << "&lt;"; break;
        case '>': ost << "&gt;"; break;
        case '\n': ost << "\n"; 
          //lcnt = 0; 
          break;
        default: ost << ch;
        }
      //lcnt ++;
      }
    //if ( lcnt > 120 )
    //  {
    //  ost << "\n";
    //  lcnt = 0;
    //  }
    }
  return ost.str();
}

//----------------------------------------------------------------------
