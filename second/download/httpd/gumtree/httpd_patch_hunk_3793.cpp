     const char *errmsg;
     apr_dbd_results_t *res = NULL;
     apr_dbd_row_t *row = NULL;
     char *ret = NULL;
     int n = 0;
     ap_dbd_t *db = dbd_acquire(r);
+    
+    if (db == NULL) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02963)
+                      "rewritemap: No db handle available! "
+                      "Check your database access");
+        return NULL;
+   }
 
     stmt = apr_hash_get(db->prepared, label, APR_HASH_KEY_STRING);
 
     rv = apr_dbd_pvselect(db->driver, r->pool, db->handle, &res,
                           stmt, 0, key, NULL);
     if (rv != 0) {
