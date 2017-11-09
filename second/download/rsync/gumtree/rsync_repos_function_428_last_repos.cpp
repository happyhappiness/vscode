static BOOL Section( FILE *InFile, BOOL (*sfunc)(char *) )
  /* ------------------------------------------------------------------------ **
   * Scan a section name, and pass the name to function sfunc().
   *
   *  Input:  InFile  - Input source.
   *          sfunc   - Pointer to the function to be called if the section
   *                    name is successfully read.
   *
   *  Output: True if the section name was read and True was returned from
   *          <sfunc>.  False if <sfunc> failed or if a lexical error was
   *          encountered.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  int   c;
  int   i;
  int   end;
  char *func  = "params.c:Section() -";

  i = 0;      /* <i> is the offset of the next free byte in bufr[] and  */
  end = 0;    /* <end> is the current "end of string" offset.  In most  */
              /* cases these will be the same, but if the last          */
              /* character written to bufr[] is a space, then <end>     */
              /* will be one less than <i>.                             */

  c = EatWhitespace( InFile );    /* We've already got the '['.  Scan */
                                  /* past initial white space.        */

  while( (EOF != c) && (c > 0) )
    {

    /* Check that the buffer is big enough for the next character. */
    if( i > (bSize - 2) )
      {
      bSize += BUFR_INC;
      bufr   = realloc_array( bufr, char, bSize );
      if( NULL == bufr )
        {
        rprintf(FLOG, "%s Memory re-allocation failure.", func);
        return( False );
        }
      }

    /* Handle a single character. */
    switch( c )
      {
      case ']':                       /* Found the closing bracket.         */
        bufr[end] = '\0';
        if( 0 == end )                  /* Don't allow an empty name.       */
          {
          rprintf(FLOG, "%s Empty section name in config file.\n", func );
          return( False );
          }
        if( !sfunc( bufr ) )            /* Got a valid name.  Deal with it. */
          return( False );
        (void)EatComment( InFile );     /* Finish off the line.             */
        return( True );

      case '\n':                      /* Got newline before closing ']'.    */
        i = Continuation( bufr, i );    /* Check for line continuation.     */
        if( i < 0 )
          {
          bufr[end] = '\0';
          rprintf(FLOG, "%s Badly formed line in config file: %s\n",
                   func, bufr );
          return( False );
          }
        end = ( (i > 0) && (' ' == bufr[i - 1]) ) ? (i - 1) : (i);
        c = getc( InFile );             /* Continue with next line.         */
        break;

      default:                        /* All else are a valid name chars.   */
        if( isspace( c ) )              /* One space per whitespace region. */
          {
          bufr[end] = ' ';
          i = end + 1;
          c = EatWhitespace( InFile );
          }
        else                            /* All others copy verbatim.        */
          {
          bufr[i++] = c;
          end = i;
          c = getc( InFile );
          }
      }
    }

  /* We arrive here if we've met the EOF before the closing bracket. */
  rprintf(FLOG, "%s Unexpected EOF in the config file: %s\n", func, bufr );
  return( False );
  }