     case APR_SUCCESS:
         break;
     }
     *db = rec;
     rv = dbd_prepared_init(rec->pool, svr, rec);
     if (rv != APR_SUCCESS) {
+        const char *errmsg = apr_dbd_error(rec->driver, rec->handle, rv);
         ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, rec->pool,
-                      "DBD: failed to initialise prepared SQL statements");
+                      "DBD: failed to initialise prepared SQL statements: %s",
+                      (errmsg ? errmsg : "[???]"));
     }
     return rv;
 }
 static apr_status_t dbd_close(void *CONN)
 {
     ap_dbd_t *conn = CONN;
