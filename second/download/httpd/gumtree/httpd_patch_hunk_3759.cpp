         return SSL_TLSEXT_ERR_NOACK;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01952)
                  "stapling_cb: retrieved cached certificate data");
 
-    /* Check to see if we already have a response for this certificate */
-    stapling_mutex_on(s);
-
-    rv = stapling_get_cached_response(s, &rsp, &ok, cinf, conn->pool);
-    if (rv == FALSE) {
-        stapling_mutex_off(s);
-        return SSL_TLSEXT_ERR_ALERT_FATAL;
-    }
-
-    if (rsp) {
-        /* see if response is acceptable */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01953)
-                     "stapling_cb: retrieved cached response");
-        rv = stapling_check_response(s, mctx, cinf, rsp, NULL);
-        if (rv == SSL_TLSEXT_ERR_ALERT_FATAL) {
-            OCSP_RESPONSE_free(rsp);
-            stapling_mutex_off(s);
-            return SSL_TLSEXT_ERR_ALERT_FATAL;
-        }
-        else if (rv == SSL_TLSEXT_ERR_NOACK) {
-            /* Error in response. If this error was not present when it was
-             * stored (i.e. response no longer valid) then it can be
-             * renewed straight away.
-             *
-             * If the error *was* present at the time it was stored then we
-             * don't renew the response straight away we just wait for the
-             * cached response to expire.
-             */
-            if (ok) {
-                OCSP_RESPONSE_free(rsp);
-                rsp = NULL;
-            }
-            else if (!mctx->stapling_return_errors) {
-                OCSP_RESPONSE_free(rsp);
-                stapling_mutex_off(s);
-                return SSL_TLSEXT_ERR_NOACK;
-            }
-        }
+    rv = get_and_check_cached_response(s, mctx, &rsp, cinf, conn->pool);
+    if (rv != 0) {
+        return rv;
     }
 
     if (rsp == NULL) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01954)
                      "stapling_cb: renewing cached response");
-        rv = stapling_renew_response(s, mctx, ssl, cinf, &rsp, conn->pool);
-
-        if (rv == FALSE) {
-            stapling_mutex_off(s);
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01955)
-                         "stapling_cb: fatal error");
-            return SSL_TLSEXT_ERR_ALERT_FATAL;
+        stapling_refresh_mutex_on(s);
+        /* Maybe another request refreshed the OCSP response while this
+         * thread waited for the mutex.  Check again.
+         */
+        rv = get_and_check_cached_response(s, mctx, &rsp, cinf, conn->pool);
+        if (rv != 0) {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                         "stapling_cb: error checking for cached response "
+                         "after obtaining refresh mutex");
+            stapling_refresh_mutex_off(s);
+            return rv;
+        }
+        else if (rsp) {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                         "stapling_cb: don't need to refresh cached response "
+                         "after obtaining refresh mutex");
+            stapling_refresh_mutex_off(s);
+        }
+        else {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                         "stapling_cb: still must refresh cached response "
+                         "after obtaining refresh mutex");
+            rv = stapling_renew_response(s, mctx, ssl, cinf, &rsp, conn->pool);
+            stapling_refresh_mutex_off(s);
+
+            if (rv == TRUE) {
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                             "stapling_cb: success renewing response");
+            }
+            else {
+                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01955)
+                             "stapling_cb: fatal error renewing response");
+                return SSL_TLSEXT_ERR_ALERT_FATAL;
+            }
         }
     }
-    stapling_mutex_off(s);
 
     if (rsp) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01956)
                      "stapling_cb: setting response");
         if (!stapling_set_response(ssl, rsp))
             return SSL_TLSEXT_ERR_ALERT_FATAL;
