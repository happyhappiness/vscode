(retVal == 0) {
         if (noisy)
            fprintf ( stderr, 
                      "%s: Deleting output file %s, if it exists.\n",
                      progName, outName );
         if (outputHandleJustInCase != NULL)
            fclose ( outputHandleJustInCase );
         retVal = remove ( outName );
         if (retVal != 0)
            fprintf ( stderr,
                      "%s: WARNING: deletion of output file "
                      "(apparently) failed.\n",
                      progName );
      } else {
         fprintf ( stderr,
                   "%s: WARNING: deletion of output file suppressed\n",
                    progName );
         fprintf ( stderr,
                   "%s:    since input file no longer exists.  Output file\n",
                   progName );
         fprintf ( stderr,
                   "%s:    `%s' may be incomplete.\n",
                   progName, outName );
         fprintf ( stderr, 
                   "%s:    I suggest doing an integrity test (bzip2 -tv)"
                   " of it.\n",
                   progName );
      }