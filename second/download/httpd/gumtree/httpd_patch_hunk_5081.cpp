         /* reset the expiry back to maxage, if the expiry is present */
         if (dconf->maxage) {
             z->expiry = now + dconf->maxage * APR_USEC_PER_SEC;
             z->maxage = dconf->maxage;
         }
 
+        /* reset the expiry before saving if present */
+        if (z->dirty && z->maxage) {
+            z->expiry = now + z->maxage * APR_USEC_PER_SEC;
+        } 
+
         /* encode the session */
         rv = ap_run_session_encode(r, z);
         if (OK != rv) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01820)
                           "error while encoding the session, "
                           "session not saved: %s", r->uri);
