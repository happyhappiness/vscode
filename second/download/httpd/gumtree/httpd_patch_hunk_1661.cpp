             worker->s->status &= ~PROXY_WORKER_IN_ERROR;
             ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                          "proxy: %s: worker for (%s) has been marked for retry",
                          proxy_function, worker->hostname);
             return OK;
         }
-        else
+        else {
             return DECLINED;
+        }
     }
-    else
+    else {
         return OK;
+    }
 }
 
 PROXY_DECLARE(int) ap_proxy_acquire_connection(const char *proxy_function,
                                                proxy_conn_rec **conn,
                                                proxy_worker *worker,
                                                server_rec *s)
