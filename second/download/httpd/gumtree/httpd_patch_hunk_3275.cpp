     c->conn_config = ap_create_conn_config(ptrans);
     c->notes = apr_table_make(ptrans, 5);
 
     c->pool = ptrans;
     if ((rv = apr_socket_addr_get(&c->local_addr, APR_LOCAL, csd))
         != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_INFO, rv, server,
+        ap_log_error(APLOG_MARK, APLOG_INFO, rv, server, APLOGNO(00137)
                      "apr_socket_addr_get(APR_LOCAL)");
         apr_socket_close(csd);
         return NULL;
     }
 
     apr_sockaddr_ip_get(&c->local_ip, c->local_addr);
-    if ((rv = apr_socket_addr_get(&c->remote_addr, APR_REMOTE, csd))
+    if ((rv = apr_socket_addr_get(&c->client_addr, APR_REMOTE, csd))
         != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_INFO, rv, server,
+        ap_log_error(APLOG_MARK, APLOG_INFO, rv, server, APLOGNO(00138)
                      "apr_socket_addr_get(APR_REMOTE)");
         apr_socket_close(csd);
         return NULL;
     }
 
-    apr_sockaddr_ip_get(&c->remote_ip, c->remote_addr);
+    apr_sockaddr_ip_get(&c->client_ip, c->client_addr);
     c->base_server = server;
 
     c->id = id;
     c->bucket_alloc = alloc;
 
-    c->cs = (conn_state_t *)apr_pcalloc(ptrans, sizeof(conn_state_t));
-    APR_RING_INIT(&(c->cs->timeout_list), conn_state_t, timeout_list);
-    c->cs->expiration_time = 0;
-    c->cs->state = CONN_STATE_CHECK_REQUEST_LINE_READABLE;
-    c->cs->c = c;
-    c->cs->p = ptrans;
-    c->cs->bucket_alloc = alloc;
     c->clogging_input_filters = 0;
 
     return c;
 }
 
 static int core_pre_connection(conn_rec *c, void *csd)
