static int EatComment( FILE *InFile )
  /* ------------------------------------------------------------------------ **
   * Scan to the end of a comment.
   *
   *  Input:  InFile  - Input source.
   *
   *  Output: The character that marks the end of the comment.  Normally,
   *          this will be a newline, but it *might* be an EOF.
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

  for( c = getc( InFile ); ('\n'!=c) && (EOF!=c) && (c>0); c = getc( InFile ) )
    ;
  return( c );
  }