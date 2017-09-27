                          "(requirement expression not fulfilled)",
                          r->filename, r->connection->remote_ip);
 
             ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                          "Failed expression: %s", req->cpExpr);
 
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "access to %s failed, reason: %s",
                           r->filename,
                           "SSL requirement expression not fulfilled "
                           "(see SSL logfile for more details)");
 
             /* remember forbidden access for strict require option */
