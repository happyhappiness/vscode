         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01143)
                       "Running scheme %s handler (attempt %d)",
                       scheme, attempts);
         AP_PROXY_RUN(r, worker, conf, url, attempts);
         access_status = proxy_run_scheme_handler(r, worker, conf,
                                                  url, NULL, 0);
-        if (access_status == OK)
+        if (access_status == OK
+                || apr_table_get(r->notes, "proxy-error-override"))
             break;
         else if (access_status == HTTP_INTERNAL_SERVER_ERROR) {
             /* Unrecoverable server error.
              * We can not failover to another worker.
              * Mark the worker as unusable if member of load balancer
              */
