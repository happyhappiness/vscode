         }
 #endif
     }
     else
 #endif
     {
+        void *conn;
+
+        rv = connection_constructor(&conn, worker, worker->cp->pool);
+        worker->cp->conn = conn;
 
-        rv = connection_constructor((void **)&(worker->cp->conn), worker, worker->cp->pool);
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
              "proxy: initialized single connection worker %d in child %" APR_PID_T_FMT " for (%s)",
              worker->id, getpid(), worker->hostname);
     }
     if (rv == APR_SUCCESS) {
         worker->status |= (PROXY_WORKER_INITIALIZED);
