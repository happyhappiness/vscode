             ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                          "core_output_filter: writing data to the network");
 
             if (more)
                 apr_brigade_destroy(more);
 
-            if (APR_STATUS_IS_ECONNABORTED(rv)
-                || APR_STATUS_IS_ECONNRESET(rv)
-                || APR_STATUS_IS_EPIPE(rv)) {
+            /* No need to check for SUCCESS, we did that above. */
+            if (!APR_STATUS_IS_EAGAIN(rv)) {
                 c->aborted = 1;
             }
 
             /* The client has aborted, but the request was successful. We
              * will report success, and leave it to the access and error
              * logs to note that the connection was aborted.
