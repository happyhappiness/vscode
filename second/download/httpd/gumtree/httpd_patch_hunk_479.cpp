 
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                      "proxy: connection complete to %pI (%s)",
                      p_conn->addr, p_conn->name);
 
         /* set up the connection filters */
-        ap_run_pre_connection(*origin, p_conn->sock);
+        rc = ap_run_pre_connection(*origin, p_conn->sock);
+        if (rc != OK && rc != DONE) {
+            (*origin)->aborted = 1;
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                         "proxy: HTTP: pre_connection setup failed (%d)",
+                         rc);
+            return rc;
+        }
     }
     return OK;
 }
 
 static
 apr_status_t ap_proxy_http_request(apr_pool_t *p, request_rec *r,
