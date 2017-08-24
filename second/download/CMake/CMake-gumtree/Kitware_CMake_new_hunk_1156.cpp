  for ( ;*pos; ++pos)
    {
    char ch = *pos;
    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 
         && ch != '\r' )
      {
      char buffer[33];
      sprintf(buffer, "&lt;%d&gt;", (int)ch);
