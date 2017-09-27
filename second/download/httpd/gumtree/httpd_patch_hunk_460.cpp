         fprintf(stderr, "Unable to open stdin\n");
         exit(1);
     }
 
     for (;;) {
         nRead = sizeof(buf);
-        if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS)
+        if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS) {
             exit(3);
+        }
         if (tRotation) {
+            /*
+             * Check for our UTC offset every time through the loop, since
+             * it might change if there's a switch between standard and
+             * daylight savings time.
+             */
+            if (use_localtime) {
+                apr_time_exp_t lt;
+                apr_time_exp_lt(&lt, apr_time_now());
+                utc_offset = lt.tm_gmtoff;
+            }
             now = (int)(apr_time_now() / APR_USEC_PER_SEC) + utc_offset;
             if (nLogFD != NULL && now >= tLogEnd) {
                 nLogFDprev = nLogFD;
                 nLogFD = NULL;
             }
         }
