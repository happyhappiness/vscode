             apr_table_setn(r->notes, "ssl-access-forbidden", "1");
 
             return HTTP_FORBIDDEN;
         }
 
         if (ok != 1) {
-            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
-                         "Access to %s denied for %s "
-                         "(requirement expression not fulfilled)",
-                         r->filename, r->connection->remote_ip);
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                          "Access to %s denied for %s "
+                          "(requirement expression not fulfilled)",
+                          r->filename, r->connection->remote_ip);
 
-            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
-                         "Failed expression: %s", req->cpExpr);
+            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
+                          "Failed expression: %s", req->cpExpr);
 
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "access to %s failed, reason: %s",
                           r->filename,
                           "SSL requirement expression not fulfilled "
                           "(see SSL logfile for more details)");
