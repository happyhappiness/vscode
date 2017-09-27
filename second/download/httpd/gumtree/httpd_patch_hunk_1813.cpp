         apr_snprintf(buf, sizeof(buf),
                  "apr_sockaddr_info_get() for %s", connecthost);
         apr_err(buf, rv);
     }
 
     /* ok - lets start */
-    start = apr_time_now();
+    start = lasttime = apr_time_now();
+    stoptime = tlimit ? (start + apr_time_from_sec(tlimit)) : AB_MAX;
+
+#ifdef SIGINT 
+    /* Output the results if the user terminates the run early. */
+    apr_signal(SIGINT, output_results);
+#endif
 
     /* initialise lots of requests */
     for (i = 0; i < concurrency; i++) {
         con[i].socknum = i;
         start_connect(&con[i]);
     }
 
-    while (done < requests) {
+    do {
         apr_int32_t n;
-        apr_int32_t timed;
-            const apr_pollfd_t *pollresults;
-
-        /* check for time limit expiry */
-        now = apr_time_now();
-        timed = (apr_int32_t)apr_time_sec(now - start);
-        if (tlimit && timed >= tlimit) {
-            requests = done;    /* so stats are correct */
-            break;      /* no need to do another round */
-        }
+        const apr_pollfd_t *pollresults;
 
         n = concurrency;
         status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
         if (status != APR_SUCCESS)
             apr_err("apr_poll", status);
 
