                 apr_strftime(buf2, &rs, sizeof(buf2), szLogRoot, &e);
             }
             else {
                 sprintf(buf2, "%s.%010d", szLogRoot, tLogStart);
             }
             tLogEnd = tLogStart + tRotation;
-            apr_file_open(&nLogFD, buf2, APR_READ | APR_WRITE | APR_CREATE | APR_APPEND,
-                          APR_OS_DEFAULT, pool);
-            if (nLogFD == NULL) {
+            rv = apr_file_open(&nLogFD, buf2, APR_WRITE | APR_CREATE | APR_APPEND,
+                               APR_OS_DEFAULT, pool);
+            if (rv != APR_SUCCESS) {
+                char error[120];
+
+                apr_strerror(rv, error, sizeof error);
+
                 /* Uh-oh. Failed to open the new log file. Try to clear
                  * the previous log file, note the lost log entries,
                  * and keep on truckin'. */
                 if (nLogFDprev == NULL) {
-                    fprintf(stderr, "1 Previous file handle doesn't exists %s\n", buf2);
+                    fprintf(stderr, "Could not open log file '%s' (%s)\n", buf2, error);
                     exit(2);
                 }
                 else {
                     nLogFD = nLogFDprev;
-                    sprintf(errbuf,
-                            "Resetting log file due to error opening "
-                            "new log file. %10d messages lost.\n",
-                            nMessCount);
+                    /* Try to keep this error message constant length
+                     * in case it occurs several times. */
+                    apr_snprintf(errbuf, sizeof errbuf,
+                                 "Resetting log file due to error opening "
+                                 "new log file, %10d messages lost: %-25.25s\n",
+                                 nMessCount, error);
                     nWrite = strlen(errbuf);
                     apr_file_trunc(nLogFD, 0);
                     if (apr_file_write(nLogFD, errbuf, &nWrite) != APR_SUCCESS) {
                         fprintf(stderr, "Error writing to the file %s\n", buf2);
                         exit(2);
                     }
