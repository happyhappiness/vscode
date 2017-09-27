     if (!dconf || !dconf->enabled) {
         return APR_SUCCESS;
     }
 
     /* should the session be loaded at all? */
     if (!session_included(r, dconf)) {
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, SESSION_PREFIX
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01814)
                       "excluded by configuration for: %s", r->uri);
         return APR_SUCCESS;
     }
 
     /* load the session from the session hook */
     rv = ap_run_session_load(r, &zz);
     if (DECLINED == rv) {
-        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, SESSION_PREFIX
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01815)
                       "session is enabled but no session modules have been configured, "
                       "session not loaded: %s", r->uri);
         return APR_EGENERAL;
     }
     else if (OK != rv) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, SESSION_PREFIX
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01816)
                       "error while loading the session, "
                       "session not loaded: %s", r->uri);
         return rv;
     }
 
     /* found a session that hasn't expired? */
