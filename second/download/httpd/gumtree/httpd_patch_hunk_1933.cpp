     } else {
         c->ssl = NULL;
     }
 #endif
     if ((rv = apr_socket_connect(c->aprsock, destsa)) != APR_SUCCESS) {
         if (APR_STATUS_IS_EINPROGRESS(rv)) {
-            apr_pollfd_t new_pollfd;
-            c->state = STATE_CONNECTING;
+            set_conn_state(c, STATE_CONNECTING);
             c->rwrite = 0;
-            new_pollfd.desc_type = APR_POLL_SOCKET;
-            new_pollfd.reqevents = APR_POLLOUT;
-            new_pollfd.desc.s = c->aprsock;
-            new_pollfd.client_data = c;
-            apr_pollset_add(readbits, &new_pollfd);
             return;
         }
         else {
-            apr_pollfd_t remove_pollfd;
-            remove_pollfd.desc_type = APR_POLL_SOCKET;
-            remove_pollfd.desc.s = c->aprsock;
-            apr_pollset_remove(readbits, &remove_pollfd);
+            set_conn_state(c, STATE_UNCONNECTED);
             apr_socket_close(c->aprsock);
             err_conn++;
             if (bad++ > 10) {
                 fprintf(stderr,
                    "\nTest aborted after 10 failures\n\n");
                 apr_err("apr_socket_connect()", rv);
             }
-            c->state = STATE_UNCONNECTED;
+            
             start_connect(c);
             return;
         }
     }
 
     /* connected first time */
-    c->state = STATE_CONNECTED;
-    started++;
+    set_conn_state(c, STATE_CONNECTED);
 #ifdef USE_SSL
     if (c->ssl) {
         ssl_proceed_handshake(c);
     } else
 #endif
     {
