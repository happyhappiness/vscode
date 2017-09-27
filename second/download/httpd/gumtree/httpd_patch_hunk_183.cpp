     apr_status_t rv;
 
     if (mc->nMutexMode == SSL_MUTEXMODE_NONE) 
         return TRUE;
 
     if ((rv = apr_global_mutex_create(&mc->pMutex, mc->szMutexFile,
-                                APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
-                     "Cannot create SSLMutex file `%s'",
-                     mc->szMutexFile);
+                                mc->nMutexMech, p)) != APR_SUCCESS) {
+        if (mc->szMutexFile)
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                         "Cannot create SSLMutex with file `%s'",
+                         mc->szMutexFile);
+        else
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                         "Cannot create SSLMutex");
         return FALSE;
     }
+#if APR_HAS_FLOCK_SERIALIZE
+    if (mc->szMutexFile && mc->ChownMutexFile == TRUE)
+        chown(mc->szMutexFile, unixd_config.user_id, -1);
+#endif
 
+#if APR_HAS_SYSVSEM_SERIALIZE
 #if APR_USE_SYSVSEM_SERIALIZE
-    rv = unixd_set_global_mutex_perms(mc->pMutex);
-    if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
-                     "Could not set permissions on ssl_mutex; check User "
-                     "and Group directives");
-        return FALSE;
+    if (mc->nMutexMech == APR_LOCK_DEFAULT || 
+        mc->nMutexMech == APR_LOCK_SYSVSEM) {
+#else
+    if (mc->nMutexMech == APR_LOCK_SYSVSEM) {
+#endif
+        rv = unixd_set_global_mutex_perms(mc->pMutex);
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                         "Could not set permissions on ssl_mutex; check User "
+                         "and Group directives");
+            return FALSE;
+        }
     }
 #endif
     return TRUE;
 }
 
 int ssl_mutex_reinit(server_rec *s, apr_pool_t *p)
 {
     SSLModConfigRec *mc = myModConfig(s);
+    apr_status_t rv;
 
     if (mc->nMutexMode == SSL_MUTEXMODE_NONE)
         return TRUE;
 
-    if (apr_global_mutex_child_init(&mc->pMutex,
-                                    mc->szMutexFile, p) != APR_SUCCESS)
+    if ((rv = apr_global_mutex_child_init(&mc->pMutex,
+                                    mc->szMutexFile, p)) != APR_SUCCESS) {
+        if (mc->szMutexFile)
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                         "Cannot reinit SSLMutex with file `%s'",
+                         mc->szMutexFile);
+        else
+            ap_log_error(APLOG_MARK, APLOG_WARNING, rv, s,
+                         "Cannot reinit SSLMutex");
         return FALSE;
+    }
     return TRUE;
 }
 
 int ssl_mutex_on(server_rec *s)
 {
     SSLModConfigRec *mc = myModConfig(s);
