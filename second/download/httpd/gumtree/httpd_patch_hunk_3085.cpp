         err = apr_sockaddr_info_get(&(worker->cp->addr),
                                     conn->hostname, APR_UNSPEC,
                                     conn->port, 0,
                                     worker->cp->pool);
         conn->addr = worker->cp->addr;
         if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, uerr, r->server,
-                         "proxy: unlock");
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, uerr, r, APLOGNO(00946) "unlock");
         }
     }
     else {
         conn->addr = worker->cp->addr;
     }
     /* Close a possible existing socket if we are told to do so */
