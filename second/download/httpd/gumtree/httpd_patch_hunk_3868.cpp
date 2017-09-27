     /* Flush any remaining output */
     apr_file_flush(outfile);
 
     if (stats) {
         apr_file_t *statsfile;
         if (apr_file_open(&statsfile, stats,
-                       APR_FOPEN_WRITE | APR_FOPEN_CREATE | APR_FOPEN_TRUNCATE,
+                          APR_FOPEN_WRITE | APR_FOPEN_CREATE | APR_FOPEN_TRUNCATE,
                           APR_OS_DEFAULT, pool) != APR_SUCCESS) {
             apr_file_printf(errfile, "%s: Could not open %s for writing.",
                             shortname, stats);
             return 1;
         }
         print_statistics(statsfile);
