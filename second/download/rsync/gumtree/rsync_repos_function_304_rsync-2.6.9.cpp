BOOL pm_process( char *FileName,
                 BOOL (*sfunc)(char *),
                 BOOL (*pfunc)(char *, char *) )
  /* ------------------------------------------------------------------------ **
   * Process the named parameter file.
   *
   *  Input:  FileName  - The pathname of the parameter file to be opened.
   *          sfunc     - A pointer to a function that will be called when
   *                      a section name is discovered.
   *          pfunc     - A pointer to a function that will be called when
   *                      a parameter name and value are discovered.
   *
   *  Output: TRUE if the file was successfully parsed, else FALSE.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  int   result;
  FILE *InFile;
  char *func = "params.c:pm_process() -";

  InFile = OpenConfFile( FileName );          /* Open the config file. */
  if( NULL == InFile )
    return( False );

  if( NULL != bufr )                          /* If we already have a buffer */
    result = Parse( InFile, sfunc, pfunc );   /* (recursive call), then just */
                                              /* use it.                     */

  else                                        /* If we don't have a buffer   */
    {                                         /* allocate one, then parse,   */
    bSize = BUFR_INC;                         /* then free.                  */
    bufr = new_array( char, bSize );
    if( NULL == bufr )
      {
      rprintf(FERROR,"%s memory allocation failure.\n", func);
      fclose(InFile);
      return( False );
      }
    result = Parse( InFile, sfunc, pfunc );
    free( bufr );
    bufr  = NULL;
    bSize = 0;
    }

  fclose(InFile);

  if( !result )                               /* Generic failure. */
    {
    rprintf(FERROR,"%s Failed.  Error returned from params.c:parse().\n", func);
    return( False );
    }

  return( True );                             /* Generic success. */
  }