     apr_status_t rv;
 
     if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
         return TRUE;
     if ((rv = apr_global_mutex_lock(mc->pMutex)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
-                     "Failed to acquire global mutex lock");
+                     "Failed to acquire SSL session cache lock");
         return FALSE;
     }
     return TRUE;
 }
 
 int ssl_mutex_off(server_rec *s)
