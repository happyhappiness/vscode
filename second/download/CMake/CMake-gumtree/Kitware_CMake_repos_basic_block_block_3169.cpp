{
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