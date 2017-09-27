 
     /* We're done with the mutex */
     rv = apr_global_mutex_unlock(authn_cache_mutex);
     if (rv != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01683) "Failed to release mutex!");
     }
-    return;
 }
 
 #define MAX_VAL_LEN 100
 static authn_status check_password(request_rec *r, const char *user,
                                    const char *password)
 {
