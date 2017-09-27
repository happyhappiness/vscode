                 ret = apr_dbd_get_entry(db->driver, row, 0);
             }
         }
     }
     if (rv != -1) {
         errmsg = apr_dbd_error(db->driver, db->handle, rv);
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00658)
                       "rewritemap: error %s looking up %s", errmsg, key);
     }
     switch (n) {
     case 0:
         return NULL;
     case 1:
