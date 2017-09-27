         return OK;
     }
 
     if (ap_setup_listeners(s) < 1) {
         ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0,
                      NULL, APLOGNO(00451) "no listening sockets available, shutting down");
-        return DONE;
+        return !OK;
     }
 
     return OK;
 }
 
 static void winnt_child_init(apr_pool_t *pchild, struct server_rec *s)
