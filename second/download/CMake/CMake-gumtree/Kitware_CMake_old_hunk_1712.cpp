  for ( pos = 0; pos < str.size(); pos ++ )
    {
    unsigned char ch = str[pos];
    if ( (ch > 126 || ch < 32) && ch != 9 )
      {
      sprintf(buffer, "&gt;&lt;");
      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
      ost << buffer;
      }
