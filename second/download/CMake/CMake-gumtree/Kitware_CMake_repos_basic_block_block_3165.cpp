{
      fprintf ( stderr, 
                "%s: WARNING: some files have not been processed:\n"
                "%s:    %d specified on command line, %d not processed yet.\n\n",
                progName, progName,
                numFileNames, numFileNames - numFilesProcessed );
   }