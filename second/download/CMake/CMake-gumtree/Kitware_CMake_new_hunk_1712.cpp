  for ( pos = 0; pos < str.size(); pos ++ )

    {

    unsigned char ch = str[pos];

    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 )

      {

      sprintf(buffer, "&gt;%d&lt;", (int)ch);

      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);

      ost << buffer;

      }

