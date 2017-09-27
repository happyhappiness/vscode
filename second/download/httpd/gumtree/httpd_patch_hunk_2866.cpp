     stmt = apr_hash_get(db->prepared, label, APR_HASH_KEY_STRING);
 
     rv = apr_dbd_pvselect(db->driver, r->pool, db->handle, &res,
                           stmt, 0, key, NULL);
     if (rv != 0) {
         errmsg = apr_dbd_error(db->driver, db->handle, rv);
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00657)
                       "rewritemap: error %s querying for %s", errmsg, key);
         return NULL;
     }
-    while (rv = apr_dbd_get_row(db->driver, r->pool, res, &row, -1), rv == 0) {
+    while ((rv = apr_dbd_get_row(db->driver, r->pool, res, &row, -1)) == 0) {
         ++n;
         if (ret == NULL) {
             ret = apr_dbd_get_entry(db->driver, row, 0);
         }
         else {
             /* randomise crudely amongst multiple results */
