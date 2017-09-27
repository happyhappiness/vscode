         */
 
         /* handle the scheme */
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "Running scheme %s handler (attempt %d)",
                      scheme, attempts);
+        AP_PROXY_RUN(r, worker, conf, url, attempts);
         access_status = proxy_run_scheme_handler(r, worker, conf,
                                                  url, NULL, 0);
         if (access_status == OK)
             break;
         else if (access_status == HTTP_INTERNAL_SERVER_ERROR) {
             /* Unrecoverable server error.
