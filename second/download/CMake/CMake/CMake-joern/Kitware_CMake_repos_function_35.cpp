static 
void compress ( Char *name )
{
   FILE  *inStr;
   FILE  *outStr;
   Int32 n, i;
   struct MY_STAT statBuf;

   deleteOutputOnInterrupt = False;

   if (name == NULL && srcMode != SM_I2O)
      panic ( "compress: bad modes\n" );

   switch (srcMode) {
      case SM_I2O: 
         copyFileName ( inName, (Char*)"(stdin)" );
         copyFileName ( outName, (Char*)"(stdout)" ); 
         break;
      case SM_F2F: 
         copyFileName ( inName, name );
         copyFileName ( outName, name );
         strcat ( outName, ".bz2" ); 
         break;
      case SM_F2O: 
         copyFileName ( inName, name );
         copyFileName ( outName, (Char*)"(stdout)" ); 
         break;
   }

   if ( srcMode != SM_I2O && containsDubiousChars ( inName ) ) {
      if (noisy)
      fprintf ( stderr, "%s: There are no files matching `%s'.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode != SM_I2O && !fileExists ( inName ) ) {
      fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                progName, inName, strerror(errno) );
      setExit(1);
      return;
   }
   for (i = 0; i < BZ_N_SUFFIX_PAIRS; i++) {
      if (hasSuffix(inName, zSuffix[i])) {
         if (noisy)
         fprintf ( stderr, 
                   "%s: Input file %s already has %s suffix.\n",
                   progName, inName, zSuffix[i] );
         setExit(1);
         return;
      }
   }
   if ( srcMode == SM_F2F || srcMode == SM_F2O ) {
      MY_STAT(inName, &statBuf);
      if ( MY_S_ISDIR(statBuf.st_mode) ) {
         fprintf( stderr,
                  "%s: Input file %s is a directory.\n",
                  progName,inName);
         setExit(1);
         return;
      }
   }
   if ( srcMode == SM_F2F && !forceOverwrite && notAStandardFile ( inName )) {
      if (noisy)
      fprintf ( stderr, "%s: Input file %s is not a normal file.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode == SM_F2F && fileExists ( outName ) ) {
      if (forceOverwrite) {
     remove(outName);
      } else {
     fprintf ( stderr, "%s: Output file %s already exists.\n",
           progName, outName );
     setExit(1);
     return;
      }
   }
   if ( srcMode == SM_F2F && !forceOverwrite &&
        (n=countHardLinks ( inName )) > 0) {
      fprintf ( stderr, "%s: Input file %s has %d other link%s.\n",
                progName, inName, n, n > 1 ? "s" : "" );
      setExit(1);
      return;
   }

   if ( srcMode == SM_F2F ) {
      /* Save the file's meta-info before we open it.  Doing it later
         means we mess up the access times. */
      saveInputFileMetaInfo ( inName );
   }

   switch ( srcMode ) {

      case SM_I2O:
         inStr = stdin;
         outStr = stdout;
         if ( isatty ( fileno ( stdout ) ) ) {
            fprintf ( stderr,
                      "%s: I won't write compressed data to a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            setExit(1);
            return;
         };
         break;

      case SM_F2O:
         inStr = fopen ( inName, "rb" );
         outStr = stdout;
         if ( isatty ( fileno ( stdout ) ) ) {
            fprintf ( stderr,
                      "%s: I won't write compressed data to a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            if ( inStr != NULL ) fclose ( inStr );
            setExit(1);
            return;
         };
         if ( inStr == NULL ) {
            fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                      progName, inName, strerror(errno) );
            setExit(1);
            return;
         };
         break;

      case SM_F2F:
         inStr = fopen ( inName, "rb" );
         outStr = fopen_output_safely ( outName, "wb" );
         if ( outStr == NULL) {
            fprintf ( stderr, "%s: Can't create output file %s: %s.\n",
                      progName, outName, strerror(errno) );
            if ( inStr != NULL ) fclose ( inStr );
            setExit(1);
            return;
         }
         if ( inStr == NULL ) {
            fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                      progName, inName, strerror(errno) );
            if ( outStr != NULL ) fclose ( outStr );
            setExit(1);
            return;
         };
         break;

      default:
         panic ( "compress: bad srcMode" );
         break;
   }

   if (verbosity >= 1) {
      fprintf ( stderr,  "  %s: ", inName );
      pad ( inName );
      fflush ( stderr );
   }

   /*--- Now the input and output handles are sane.  Do the Biz. ---*/
   outputHandleJustInCase = outStr;
   deleteOutputOnInterrupt = True;
   compressStream ( inStr, outStr );
   outputHandleJustInCase = NULL;

   /*--- If there was an I/O error, we won't get here. ---*/
   if ( srcMode == SM_F2F ) {
      applySavedTimeInfoToOutputFile ( outName );
      deleteOutputOnInterrupt = False;
      if ( !keepInputFiles ) {
         IntNative retVal = remove ( inName );
         ERROR_IF_NOT_ZERO ( retVal );
      }
   }

   deleteOutputOnInterrupt = False;
}