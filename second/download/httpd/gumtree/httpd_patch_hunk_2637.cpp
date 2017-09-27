 
         /* Get a single line of input from the client */
         if (((rv = ap_get_brigade(c->input_filters, bb, AP_MODE_GETLINE,
                                   APR_BLOCK_READ, 0)) != APR_SUCCESS)) {
             apr_brigade_cleanup(bb);
             if (!APR_STATUS_IS_EOF(rv) && ! APR_STATUS_IS_TIMEUP(rv))
-                ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
+                ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server, APLOGNO(01611)
                              "ProtocolEcho: Failure reading from %s",
-                             c->remote_ip);
+                             c->client_ip);
             break;
         }
 
         /* Something horribly wrong happened.  Someone didn't block! */
         if (APR_BRIGADE_EMPTY(bb)) {
             apr_brigade_cleanup(bb);
-            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
+            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server, APLOGNO(01612)
                          "ProtocolEcho: Error - read empty brigade from %s!",
-                         c->remote_ip);
+                         c->client_ip);
             break;
         }
 
         if (!csd) {
-            csd = ap_get_module_config(c->conn_config, &core_module);
+            csd = ap_get_conn_socket(c);
             apr_socket_timeout_set(csd, c->base_server->keep_alive_timeout);
         }
 
         update_echo_child_status(c->sbh, SERVER_BUSY_WRITE, NULL, bb);
 
         /* Make sure the data is flushed to the client */
         b = apr_bucket_flush_create(c->bucket_alloc);
         APR_BRIGADE_INSERT_TAIL(bb, b);
         rv = ap_pass_brigade(c->output_filters, bb);
         if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
+            ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server, APLOGNO(01613)
                          "ProtocolEcho: Failure writing to %s",
-                         c->remote_ip);
-            break; 
+                         c->client_ip);
+            break;
         }
         apr_brigade_cleanup(bb);
 
         /* Announce our intent to loop */
         update_echo_child_status(c->sbh, SERVER_BUSY_KEEPALIVE, NULL, NULL);
     }
