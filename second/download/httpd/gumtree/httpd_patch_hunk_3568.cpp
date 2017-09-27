 
     if (apr_file_open_stdin(&f_stdin, status.pool) != APR_SUCCESS) {
         fprintf(stderr, "Unable to open stdin\n");
         exit(1);
     }
 
+    if (apr_file_open_stdout(&f_stdout, status.pool) != APR_SUCCESS) {
+        fprintf(stderr, "Unable to open stdout\n");
+        exit(1);
+    }
+
     /*
      * Write out result of config parsing if verbose is set.
      */
     if (config.verbose) {
         dumpConfig(&config);
     }
 
+#if APR_FILES_AS_SOCKETS
+    if (config.create_empty && config.tRotation) {
+        pollfd.p = status.pool;
+        pollfd.desc_type = APR_POLL_FILE;
+        pollfd.reqevents = APR_POLLIN;
+        pollfd.desc.f = f_stdin;
+    }
+#endif
+
     /*
      * Immediately open the logfile as we start, if we were forced
      * to do so via '-f'.
      */
     if (config.force_open) {
         doRotate(&config, &status);
     }
 
     for (;;) {
         nRead = sizeof(buf);
+#if APR_FILES_AS_SOCKETS
+        if (config.create_empty && config.tRotation) {
+            polltimeout = status.tLogEnd ? status.tLogEnd - get_now(&config) : config.tRotation;
+            if (polltimeout <= 0) {
+                pollret = APR_TIMEUP;
+            }
+            else {
+                pollret = apr_poll(&pollfd, 1, &pollret, apr_time_from_sec(polltimeout));
+            }
+        }
+        if (pollret == APR_SUCCESS) {
+            rv = apr_file_read(f_stdin, buf, &nRead);
+            if (APR_STATUS_IS_EOF(rv)) {
+                break;
+            }
+            else if (rv != APR_SUCCESS) {
+                exit(3);
+            }
+        }
+        else if (pollret == APR_TIMEUP) {
+            *buf = 0;
+            nRead = 0;
+        }
+        else {
+            fprintf(stderr, "Unable to poll stdin\n");
+            exit(5);
+        }
+#else /* APR_FILES_AS_SOCKETS */
         rv = apr_file_read(f_stdin, buf, &nRead);
-        if (rv != APR_SUCCESS) {
+        if (APR_STATUS_IS_EOF(rv)) {
+            break;
+        }
+        else if (rv != APR_SUCCESS) {
             exit(3);
         }
+#endif /* APR_FILES_AS_SOCKETS */
         checkRotate(&config, &status);
         if (status.rotateReason != ROTATE_NONE) {
             doRotate(&config, &status);
         }
 
         nWrite = nRead;
-        rv = apr_file_write(status.nLogFD, buf, &nWrite);
+        rv = apr_file_write(status.current.fd, buf, &nWrite);
         if (rv == APR_SUCCESS && nWrite != nRead) {
             /* buffer partially written, which for rotatelogs means we encountered
              * an error such as out of space or quota or some other limit reached;
              * try to write the rest so we get the real error code
              */
             apr_size_t nWritten = nWrite;
 
             nRead  = nRead - nWritten;
             nWrite = nRead;
-            rv = apr_file_write(status.nLogFD, buf + nWritten, &nWrite);
+            rv = apr_file_write(status.current.fd, buf + nWritten, &nWrite);
         }
         if (nWrite != nRead) {
             char strerrbuf[120];
             apr_off_t cur_offset;
 
             cur_offset = 0;
-            if (apr_file_seek(status.nLogFD, APR_CUR, &cur_offset) != APR_SUCCESS) {
+            if (apr_file_seek(status.current.fd, APR_CUR, &cur_offset) != APR_SUCCESS) {
                 cur_offset = -1;
             }
             apr_strerror(rv, strerrbuf, sizeof strerrbuf);
             status.nMessCount++;
             apr_snprintf(status.errbuf, sizeof status.errbuf,
                          "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
                          "%10d messages lost (%s)\n",
                          rv, cur_offset, status.nMessCount, strerrbuf);
             nWrite = strlen(status.errbuf);
-            apr_file_trunc(status.nLogFD, 0);
-            if (apr_file_write(status.nLogFD, status.errbuf, &nWrite) != APR_SUCCESS) {
-                fprintf(stderr, "Error writing to the file %s\n", status.filename);
+            apr_file_trunc(status.current.fd, 0);
+            if (apr_file_write(status.current.fd, status.errbuf, &nWrite) != APR_SUCCESS) {
+                fprintf(stderr, "Error writing to the file %s\n", status.current.name);
                 exit(2);
             }
         }
         else {
             status.nMessCount++;
         }
+        if (config.echo) {
+            if (apr_file_write_full(f_stdout, buf, nRead, &nWrite)) {
+                fprintf(stderr, "Unable to write to stdout\n");
+                exit(4);
+            }
+        }
     }
-    /* Of course we never, but prevent compiler warnings */
-    return 0;
+
+    return 0; /* reached only at stdin EOF. */
 }
