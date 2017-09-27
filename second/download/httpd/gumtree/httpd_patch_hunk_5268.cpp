         return result;
     }
     else {
         /*
          * We have just bound the connection to a different user and password
          * combination, which might be reused unintentionally next time this
-         * connection is used from the connection pool. To ensure no confusion,
-         * we mark the connection as unbound.
+         * connection is used from the connection pool.
          */
-        ldc->bound = 0;
+        ldc->must_rebind = 0;
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r, "LDC %pp used for authn, must be rebound", ldc);
     }
 
     /*
      * Get values for the provided attributes.
      */
     if (attrs) {
