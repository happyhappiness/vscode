                                     conn->hostname, APR_UNSPEC,
                                     conn->port, 0,
                                     conn->pool);
     }
     else if (!worker->cp->addr) {
         if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server,
-                         "proxy: lock");
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, err, r, APLOGNO(00945) "lock");
             return HTTP_INTERNAL_SERVER_ERROR;
         }
 
         /*
          * Worker can have the single constant backend adress.
          * The single DNS lookup is used once per worker.
