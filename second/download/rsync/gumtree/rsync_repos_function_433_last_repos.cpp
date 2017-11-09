static int Parse( FILE *InFile,
                   BOOL (*sfunc)(char *),
                   BOOL (*pfunc)(char *, char *) )
  /* ------------------------------------------------------------------------ **
   * Scan & parse the input.
   *
   *  Input:  InFile  - Input source.
   *          sfunc   - Function to be called when a section name is scanned.
   *                    See Section().
   *          pfunc   - Function to be called when a parameter is scanned.
   *                    See Parameter().
   *
   *  Output: 1 if the file was successfully scanned, 2 if the file was
   *  scanned until a section header with no section function, else 0.
   *
   *  Notes:  The input can be viewed in terms of 'lines'.  There are four
   *          types of lines:
   *            Blank      - May contain whitespace, otherwise empty.
   *            Comment    - First non-whitespace character is a ';' or '#'.
   *                         The remainder of the line is ignored.
   *            Section    - First non-whitespace character is a '['.
   *            Parameter  - The default case.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  int    c;

  c = EatWhitespace( InFile );
  while( (EOF != c) && (c > 0) )
    {
    switch( c )
      {
      case '\n':                        /* Blank line. */
        c = EatWhitespace( InFile );
        break;

      case ';':                         /* Comment line. */
      case '#':
        c = EatComment( InFile );
        break;

      case '[':                         /* Section Header. */
        if (!sfunc)
          return 2;
        if( !Section( InFile, sfunc ) )
          return 0;
        c = EatWhitespace( InFile );
        break;

      case '\\':                        /* Bogus backslash. */
        c = EatWhitespace( InFile );
        break;

      case '&':                         /* Handle directives */
        the_sfunc = sfunc;
        the_pfunc = pfunc;
        c = Parameter( InFile, parse_directives, c );
        if (c != 1)
          return c;
        c = EatWhitespace( InFile );
        break;

      default:                          /* Parameter line. */
        if( !Parameter( InFile, pfunc, c ) )
          return 0;
        c = EatWhitespace( InFile );
        break;
      }
    }
  return 1;
  }