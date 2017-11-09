static int EatWhitespace( FILE *InFile )
  /* ------------------------------------------------------------------------ **
   * Scan past whitespace (see ctype(3C)) and return the first non-whitespace
   * character, or newline, or EOF.
   *
   *  Input:  InFile  - Input source.
   *
   *  Output: The next non-whitespace character in the input stream.
   *
   *  Notes:  Because the config files use a line-oriented grammar, we
   *          explicitly exclude the newline character from the list of
   *          whitespace characters.
   *        - Note that both EOF (-1) and the nul character ('\0') are
   *          considered end-of-file markers.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  int c;

  for( c = getc( InFile ); isspace( c ) && ('\n' != c); c = getc( InFile ) )
    ;
  return( c );
  }