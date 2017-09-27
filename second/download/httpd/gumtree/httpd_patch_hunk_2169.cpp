         }
     }
 
     if (ret == HTTP_FORBIDDEN
         && (ap_satisfies(r) != SATISFY_ANY || !ap_some_auth_required(r))) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-            "client denied by server configuration: %s",
-            r->filename);
+            "client denied by server configuration: %s%s",
+            r->filename ? "" : "uri ",
+            r->filename ? r->filename : r->uri);
     }
 
     return ret;
 }
 
 static void register_hooks(apr_pool_t *p)
