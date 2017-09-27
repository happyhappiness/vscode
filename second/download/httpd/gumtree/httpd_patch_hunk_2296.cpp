     ap_rprintf(r, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>");
     ap_rprintf(r, "current entries: <b>%d</b>, current size: <b>%ld</b> bytes<br>", elts, size);
     ap_rprintf(r, "average entry size: <b>%d</b> bytes<br>", avg);
     return;
 }
 
-static apr_status_t socache_dbm_iterate(ap_socache_instance_t *instance,
-                                        server_rec *s,
+static apr_status_t socache_dbm_iterate(ap_socache_instance_t *ctx,
+                                        server_rec *s, void *userctx,
                                         ap_socache_iterator_t *iterator,
                                         apr_pool_t *pool)
 {
-    return APR_ENOTIMPL;
+    apr_dbm_t *dbm;
+    apr_datum_t dbmkey;
+    apr_datum_t dbmval;
+    apr_time_t expiry;
+    int expired;
+    apr_time_t now;
+    apr_status_t rv;
+
+    /*
+     * make sure the expired records are omitted
+     */
+    now = apr_time_now();
+    if ((rv = apr_dbm_open(&dbm, ctx->data_file, APR_DBM_RWCREATE,
+                           DBM_FILE_MODE, ctx->pool)) != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                     "Cannot open socache DBM file `%s' for "
+                     "iterating", ctx->data_file);
+        return rv;
+    }
+    rv = apr_dbm_firstkey(dbm, &dbmkey);
+    while (rv == APR_SUCCESS && dbmkey.dptr != NULL) {
+        expired = FALSE;
+        apr_dbm_fetch(dbm, dbmkey, &dbmval);
+        if (dbmval.dsize <= sizeof(apr_time_t) || dbmval.dptr == NULL)
+            expired = TRUE;
+        else {
+            memcpy(&expiry, dbmval.dptr, sizeof(apr_time_t));
+            if (expiry <= now)
+                expired = TRUE;
+        }
+        if (!expired) {
+            rv = iterator(ctx, s, userctx,
+                             (unsigned char *)dbmkey.dptr, dbmkey.dsize,
+                             (unsigned char *)dbmval.dptr + sizeof(apr_time_t),
+                             dbmval.dsize - sizeof(apr_time_t), pool);
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s,
+                         "dbm `%s' entry iterated", ctx->data_file);
+            if (rv != APR_SUCCESS)
+                return rv;
+        }
+        rv = apr_dbm_nextkey(dbm, &dbmkey);
+    }
+    apr_dbm_close(dbm);
+
+    if (rv != APR_SUCCESS && rv != APR_EOF) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                     "Failure reading first/next socache DBM file `%s' record",
+                     ctx->data_file);
+        return rv;
+    }
+    return APR_SUCCESS;
 }
 
 static const ap_socache_provider_t socache_dbm = {
     "dbm",
     AP_SOCACHE_FLAG_NOTMPSAFE,
     socache_dbm_create,
