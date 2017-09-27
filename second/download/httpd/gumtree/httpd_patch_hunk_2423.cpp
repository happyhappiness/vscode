     }
 
     /* OK, we're on.  Grab mutex to do our business */
     rv = apr_global_mutex_trylock(authn_cache_mutex);
     if (APR_STATUS_IS_EBUSY(rv)) {
         /* don't wait around; just abandon it */
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(01679)
                       "authn credentials for %s not cached (mutex busy)", user);
         return;
     }
     else if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01680)
                       "Failed to cache authn credentials for %s in %s",
                       module, dcfg->context);
         return;
     }
 
     /* We have the mutex, so go ahead */
