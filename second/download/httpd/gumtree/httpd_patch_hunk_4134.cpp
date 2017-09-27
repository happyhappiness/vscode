         /* Maybe another request refreshed the OCSP response while this
          * thread waited for the mutex.  Check again.
          */
         rv = get_and_check_cached_response(s, mctx, &rsp, &ok, cinf,
                                            conn->pool);
         if (rv != 0) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03236)
                          "stapling_cb: error checking for cached response "
                          "after obtaining refresh mutex");
             stapling_refresh_mutex_off(s);
             return rv;
         }
         else if (rsp) {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03237)
                          "stapling_cb: don't need to refresh cached response "
                          "after obtaining refresh mutex");
             stapling_refresh_mutex_off(s);
         }
         else {
-            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03238)
                          "stapling_cb: still must refresh cached response "
                          "after obtaining refresh mutex");
             rv = stapling_renew_response(s, mctx, ssl, cinf, &rsp, &ok,
                                          conn->pool);
             stapling_refresh_mutex_off(s);
 
             if (rv == TRUE) {
-                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03040)
                              "stapling_cb: success renewing response");
             }
             else {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01955)
                              "stapling_cb: fatal error renewing response");
                 return SSL_TLSEXT_ERR_ALERT_FATAL;
