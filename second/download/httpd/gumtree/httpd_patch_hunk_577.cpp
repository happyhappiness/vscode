 
     *ptr = apr_pstrdup(cmd->pool, arg);
     return NULL;
 }
 
 static int nwssl_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
-                         apr_pool_t *ptemp)
+                            apr_pool_t *ptemp)
 {
     ap_seclisteners = NULL;
     ap_seclistenersup = NULL;
     certlist = apr_array_make(pconf, 1, sizeof(char *));
 
     return OK;
 }
 
 static int nwssl_pre_connection(conn_rec *c, void *csd)
 {
-    
+
     if (apr_table_get(c->notes, "nwconv-ssl")) {
         convert_secure_socket(c, (apr_socket_t*)csd);
     }
     else {
         secsocket_data *csd_data = apr_palloc(c->pool, sizeof(secsocket_data));
 
         csd_data->csd = (apr_socket_t*)csd;
         csd_data->is_secure = 0;
         ap_set_module_config(c->conn_config, &nwssl_module, (void*)csd_data);
     }
-    
+
     return OK;
 }
 
 static int nwssl_post_config(apr_pool_t *pconf, apr_pool_t *plog,
-                          apr_pool_t *ptemp, server_rec *s)
+                             apr_pool_t *ptemp, server_rec *s)
 {
     seclisten_rec* sl;
     ap_listen_rec* lr;
     apr_socket_t*  sd;
     apr_status_t status;
     seclistenup_rec *slu;
     int found;
 
     for (sl = ap_seclisteners; sl != NULL; sl = sl->next) {
         sl->fd = find_secure_listener(sl);
 
         if (sl->fd < 0)
-            sl->fd = make_secure_socket(pconf, &sl->local_addr, sl->key, sl->mutual, s);            
-            
+            sl->fd = make_secure_socket(pconf, &sl->local_addr,
+                                        sl->key, sl->mutual, s);
+
         if (sl->fd >= 0) {
             apr_os_sock_info_t sock_info;
 
             sock_info.os_sock = &(sl->fd);
             sock_info.local = (struct sockaddr*)&(sl->local_addr);
             sock_info.remote = NULL;
             sock_info.family = APR_INET;
             sock_info.type = SOCK_STREAM;
 
             apr_os_sock_make(&sd, &sock_info, pconf);
 
             lr = apr_pcalloc(pconf, sizeof(ap_listen_rec));
-        
+
             if (lr) {
-				lr->sd = sd;
-                if ((status = apr_sockaddr_info_get(&lr->bind_addr, sl->addr, APR_UNSPEC, sl->port, 0, 
-                                              pconf)) != APR_SUCCESS) {
+                lr->sd = sd;
+                if ((status = apr_sockaddr_info_get(&lr->bind_addr, sl->addr,
+                        APR_UNSPEC, sl->port, 0, pconf)) != APR_SUCCESS) {
                     ap_log_perror(APLOG_MARK, APLOG_CRIT, status, pconf,
-                                 "alloc_listener: failed to set up sockaddr for %s:%d", sl->addr, sl->port);
+                                  "alloc_listener: failed to set up sockaddr for %s:%d",
+                                  sl->addr, sl->port);
                     return HTTP_INTERNAL_SERVER_ERROR;
                 }
                 lr->next = ap_listeners;
                 ap_listeners = lr;
                 apr_pool_cleanup_register(pconf, lr, nwssl_socket_cleanup, apr_pool_cleanup_null);
             }
         } else {
             return HTTP_INTERNAL_SERVER_ERROR;
         }
-    } 
+    }
 
     for (slu = ap_seclistenersup; slu; slu = slu->next) {
         /* Check the listener list for a matching upgradeable listener */
         found = 0;
         for (lr = ap_listeners; lr; lr = lr->next) {
             if (slu->port == lr->bind_addr->port) {
                 found = 1;
                 break;
             }
         }
         if (!found) {
             ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog,
-                         "No Listen directive found for upgradeable listener %s:%d", slu->addr, slu->port);
+                          "No Listen directive found for upgradeable listener %s:%d",
+                          slu->addr, slu->port);
         }
-    }    
+    }
 
     build_cert_list(pconf);
 
     return OK;
 }
 
