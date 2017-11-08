static BOOL Parameter( FILE *InFile, BOOL (*pfunc)(char *, char *), int c )
  /* ------------------------------------------------------------------------ **
   * Scan a parameter name and value, and pass these two fields to pfunc().
   *
   *  Input:  InFile  - The input source.
   *          pfunc   - A pointer to the function that will be called to
   *                    process the parameter, once it has been scanned.
   *          c       - The first character of the parameter name, which
   *                    would have been read by Parse().  Unlike a comment
   *                    line or a section header, there is no lead-in
   *                    character that can be discarded.
   *
   *  Output: True if the parameter name and value were scanned and processed
   *          successfully, else False.
   *
   *  Notes:  This function is in two parts.  The first loop scans the
   *          parameter name.  Internal whitespace is compressed, and an
   *          equal sign (=) terminates the token.  Leading and trailing
   *          whitespace is discarded.  The second loop scans the parameter
   *          value.  When both have been successfully identified, they are
   *          passed to pfunc() for processing.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  int   i       = 0;    /* Position within bufr. */
  int   end     = 0;    /* bufr[end] is current end-of-string. */
  int   vstart  = 0;    /* Starting position of the parameter value. */
  char *func    = "params.c:Parameter() -";

  /* Read the parameter name. */
  while( 0 == vstart )  /* Loop until we've found the start of the value. */
    {

    if( i > (bSize - 2) )       /* Ensure there's space for next char.    */
      {
      bSize += BUFR_INC;
      bufr   = Realloc( bufr, bSize );
      if( NULL == bufr )
        {
        rprintf(FERROR, "%s Memory re-allocation failure.", func) ;
        return( False );
        }
      }

    switch( c )
      {
      case '=':                 /* Equal sign marks end of param name. */
        if( 0 == end )              /* Don't allow an empty name.      */
          {
          rprintf(FERROR, "%s Invalid parameter name in config. file.\n", func );
          return( False );
          }
        bufr[end++] = '\0';         /* Mark end of string & advance.   */
        i       = end;              /* New string starts here.         */
        vstart  = end;              /* New string is parameter value.  */
        bufr[i] = '\0';             /* New string is nul, for now.     */
        break;

      case '\n':                /* Find continuation char, else error. */
        i = Continuation( bufr, i );
        if( i < 0 )
          {
          bufr[end] = '\0';
          rprintf(FERROR, "%s Ignoring badly formed line in configuration file: %s\n",
                   func, bufr );
          return( True );
          }
        end = ( (i > 0) && (' ' == bufr[i - 1]) ) ? (i - 1) : (i);
        c = getc( InFile );       /* Read past eoln.                   */
        break;

      case '\0':                /* Shouldn't have EOF within param name. */
      case EOF:
        bufr[i] = '\0';
        rprintf(FERROR, "%s Unexpected end-of-file at: %s\n", func, bufr );
        return( True );

      default:
        if( isspace( c ) )     /* One ' ' per whitespace region.       */
          {
          bufr[end] = ' ';
          i = end + 1;
          c = EatWhitespace( InFile );
          }
        else                   /* All others verbatim.                 */
          {
          bufr[i++] = c;
          end = i;
          c = getc( InFile );
          }
      }
    }

  /* Now parse the value. */
  c = EatWhitespace( InFile );  /* Again, trim leading whitespace. */
  while( (EOF !=c) && (c > 0) )
    {

    if( i > (bSize - 2) )       /* Make sure there's enough room. */
      {
      bSize += BUFR_INC;
      bufr   = Realloc( bufr, bSize );
      if( NULL == bufr )
        {
        rprintf(FERROR, "%s Memory re-allocation failure.", func) ;
        return( False );
        }
      }

    switch( c )
      {
      case '\r':              /* Explicitly remove '\r' because the older */
        c = getc( InFile );   /* version called fgets_slash() which also  */
        break;                /* removes them.                            */

      case '\n':              /* Marks end of value unless there's a '\'. */
        i = Continuation( bufr, i );
        if( i < 0 )
          c = 0;
        else
          {
          for( end = i; (end >= 0) && isspace(bufr[end]); end-- )
            ;
          c = getc( InFile );
          }
        break;

      default:               /* All others verbatim.  Note that spaces do */
        bufr[i++] = c;       /* not advance <end>.  This allows trimming  */
        if( !isspace( c ) )  /* of whitespace at the end of the line.     */
          end = i;
        c = getc( InFile );
        break;
      }
    }
  bufr[end] = '\0';          /* End of value. */

  return( pfunc( bufr, &bufr[vstart] ) );   /* Pass name & value to pfunc().  */
  }