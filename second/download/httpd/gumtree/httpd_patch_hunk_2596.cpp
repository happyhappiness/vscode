      * our pool, which is probably not what we want.  Error checking isn't
      * necessary now, but in case that changes in the future ...
      */
     rv = apr_dbd_get_driver(rec->pool, cfg->name, &rec->driver);
     if (rv != APR_SUCCESS) {
         if (APR_STATUS_IS_ENOTIMPL(rv)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
-                         "DBD: driver for %s not available", cfg->name);
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00625)
+                         "driver for %s not available", cfg->name);
         }
         else if (APR_STATUS_IS_EDSOOPEN(rv)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
-                         "DBD: can't find driver for %s", cfg->name);
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00626)
+                         "can't find driver for %s", cfg->name);
         }
         else if (APR_STATUS_IS_ESYMNOTFOUND(rv)) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
-                         "DBD: driver for %s is invalid or corrupted",
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00627)
+                         "driver for %s is invalid or corrupted",
                          cfg->name);
         }
         else {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
-                         "DBD: mod_dbd not compatible with APR in get_driver");
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00628)
+                         "mod_dbd not compatible with APR in get_driver");
         }
         apr_pool_destroy(rec->pool);
         return rv;
     }
 
     rv = apr_dbd_open_ex(rec->driver, rec->pool, cfg->params, &rec->handle, &err);
     if (rv != APR_SUCCESS) {
         switch (rv) {
         case APR_EGENERAL:
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
-                         "DBD: Can't connect to %s: %s", cfg->name, err);
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00629)
+                         "Can't connect to %s: %s", cfg->name, err);
             break;
         default:
-            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server,
-                         "DBD: mod_dbd not compatible with APR in open");
+            ap_log_error(APLOG_MARK, APLOG_ERR, rv, cfg->server, APLOGNO(00630)
+                         "mod_dbd not compatible with APR in open");
             break;
         }
 
         apr_pool_destroy(rec->pool);
         return rv;
     }
