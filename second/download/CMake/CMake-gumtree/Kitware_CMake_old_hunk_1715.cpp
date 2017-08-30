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
