 	    if ((rv & APR_POLLERR) || (rv & APR_POLLNVAL)) {
 		bad++;
 		err_except++;
 		start_connect(c);
 		continue;
 	    }
-	    if (rv & APR_POLLOUT)
-		write_request(c);
+	    if (rv & APR_POLLOUT) {
+                if (c->state == STATE_CONNECTING) {
+                    apr_pollfd_t remove_pollfd;
+                    rv = apr_connect(c->aprsock, destsa);
+                    remove_pollfd.desc_type = APR_POLL_SOCKET;
+                    remove_pollfd.desc.s = c->aprsock;
+                    apr_pollset_remove(readbits, &remove_pollfd);
+                    if (rv != APR_SUCCESS) {
+                        apr_socket_close(c->aprsock);
+                        err_conn++;
+                        if (bad++ > 10) {
+                            fprintf(stderr,
+                                    "\nTest aborted after 10 failures\n\n");
+                            apr_err("apr_connect()", rv);
+                        }
+                        c->state = STATE_UNCONNECTED;
+                        start_connect(c);
+                        continue;
+                    }
+                    else {
+                        c->state = STATE_CONNECTED;
+                        write_request(c);
+                    }
+                }
+                else {
+                    write_request(c);
+                }
+            }
 
 	    /*
 	     * When using a select based poll every time we check the bits
 	     * are reset. In 1.3's ab we copied the FD_SET's each time
 	     * through, but here we're going to check the state and if the
 	     * connection is in STATE_READ or STATE_CONNECTING we'll add the
 	     * socket back in as APR_POLLIN.
 	     */
 #ifdef USE_SSL
             if (ssl != 1)
 #endif
-	    if (c->state == STATE_READ ||
-                c->state == STATE_CONNECTING) {
+                if (c->state == STATE_READ) {
                     apr_pollfd_t new_pollfd;
                     new_pollfd.desc_type = APR_POLL_SOCKET;
                     new_pollfd.reqevents = APR_POLLIN;
                     new_pollfd.desc.s = c->aprsock;
                     new_pollfd.client_data = c;
                     apr_pollset_add(readbits, &new_pollfd);
