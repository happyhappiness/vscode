std::string cmCTest::MakeXMLSafe(const std::string& str)
{
  std::string::size_type pos = 0;
  cmOStringStream ost;
  char buffer[10];
  for ( pos = 0; pos < str.size(); pos ++ )
    {
    char ch = str[pos];
    if ( ch > 126 )
      {
      sprintf(buffer, "&%x", (int)ch);
      ost << buffer;
      }
    else
      {
      switch ( ch )
        {
        case '&': ost << "&amp;"; break;
        case '<': ost << "&lt;"; break;
        case '>': ost << "&gt;"; break;
        default: ost << ch;
        }
      }
    }
  return ost.str();
}