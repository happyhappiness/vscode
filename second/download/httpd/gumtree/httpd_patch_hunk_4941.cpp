             apr_snprintf(status.errbuf, sizeof status.errbuf,
                          "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
                          "%10d messages lost (%s)\n",
                          rv, cur_offset, status.nMessCount, strerrbuf);
             nWrite = strlen(status.errbuf);
             apr_file_trunc(status.current.fd, 0);
-            if (apr_file_write(status.current.fd, status.errbuf, &nWrite) != APR_SUCCESS) {
+            if (apr_file_write_full(status.current.fd, status.errbuf, nWrite, NULL) != APR_SUCCESS) {
                 fprintf(stderr, "Error writing to the file %s\n", status.current.name);
                 exit(2);
             }
         }
         else {
             status.nMessCount++;
