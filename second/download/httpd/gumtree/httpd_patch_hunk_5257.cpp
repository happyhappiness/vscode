                 ap_log_rerror(APLOG_MARK, APLOG_TRACE6, rv, f->r,
                               "apr_pollset_poll()");
 #else /* APR_FILES_AS_SOCKETS */
                 /* Yuck... I'd really like to wait until I can read
                  * or write, but instead I have to sleep and try again
                  */
-                apr_sleep(100000); /* 100 milliseconds */
+                apr_sleep(apr_time_from_msec(100));
                 ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, f->r, "apr_sleep()");
 #endif /* APR_FILES_AS_SOCKETS */
             }
             else if (rv != APR_SUCCESS) {
                 return rv;
             }
