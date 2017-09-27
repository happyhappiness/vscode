     /* do a DNS lookup for the destination host */
     if (!connect_addr)
         err = apr_sockaddr_info_get(&(connect_addr),
                                     connectname, APR_UNSPEC,
                                     connectport, 0,
                                     address_pool);
-    if (worker->is_address_reusable && !worker->cp->addr) {
+    if (worker->s->is_address_reusable && !worker->cp->addr) {
         worker->cp->addr = connect_addr;
-        if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, uerr, r->server,
-                         "proxy: FTP: unlock");
+        if ((uerr = PROXY_THREAD_UNLOCK(worker->balancer)) != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, uerr, r, APLOGNO(01038) "unlock");
         }
     }
     /*
      * get all the possible IP addresses for the destname and loop through
      * them until we get a successful connection
      */
