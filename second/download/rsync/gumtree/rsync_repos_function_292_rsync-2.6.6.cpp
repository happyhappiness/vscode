static FILE *OpenConfFile( char *FileName )
  /* ------------------------------------------------------------------------ **
   * Open a configuration file.
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
    rprintf(FERROR,"%s No configuration filename specified.\n", func);
    return( NULL );
    }

  OpenedFile = fopen( FileName, "r" );
  if( NULL == OpenedFile )
    {
    rsyserr(FERROR, errno, "rsync: unable to open configuration file \"%s\"",
	    safe_fname(FileName));
    }

  return( OpenedFile );
  }