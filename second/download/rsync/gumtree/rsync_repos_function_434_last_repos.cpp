static FILE *OpenConfFile( char *FileName )
  /* ------------------------------------------------------------------------ **
   * Open a config file.
   *
   *  Input:  FileName  - The pathname of the config file to be opened.
   *
   *  Output: A pointer of type (FILE *) to the opened file, or NULL if the
   *          file could not be opened.
   *
   * ------------------------------------------------------------------------ **
   */
  {
  FILE *OpenedFile;
  char *func = "params.c:OpenConfFile() -";

  if( NULL == FileName || 0 == *FileName )
    {
    rprintf(FLOG, "%s No config filename specified.\n", func);
    return( NULL );
    }

  OpenedFile = fopen( FileName, "r" );
  if( NULL == OpenedFile )
    {
    rsyserr(FLOG, errno, "unable to open config file \"%s\"",
	    FileName);
    }

  return( OpenedFile );
  }