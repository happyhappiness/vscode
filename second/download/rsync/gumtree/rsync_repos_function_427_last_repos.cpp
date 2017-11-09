static int Continuation( char *line, int pos )
  /* ------------------------------------------------------------------------ **
   * Scan backards within a string to discover if the last non-whitespace
   * character is a line-continuation character ('\\').
   *
   *  Input:  line  - A pointer to a buffer containing the string to be
   *                  scanned.
   *          pos   - This is taken to be the offset of the end of the
   *                  string.  This position is *not* scanned.
   *
   *  Output: The offset of the '\\' character if it was found, or -1 to
   *          indicate that it was not.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  pos--;
  while( pos >= 0 && isSpace(line + pos) )
     pos--;

  return( ((pos >= 0) && ('\\' == line[pos])) ? pos : -1 );
  }