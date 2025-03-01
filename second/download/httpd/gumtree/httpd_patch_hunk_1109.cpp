         }
         else if (content_length > 0) {
             ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                          "proxy: read zero bytes, expecting"
                          " %" APR_OFF_T_FMT " bytes",
                          content_length);
-            status = ajp_send_data_msg(conn->sock, msg, 0);
-            if (status != APR_SUCCESS) {
-                /* We had a failure: Close connection to backend */
-                conn->close++;
-                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
-                            "proxy: send failed to %pI (%s)",
-                            conn->worker->cp->addr,
-                            conn->worker->hostname);
-                return HTTP_INTERNAL_SERVER_ERROR;
-            }
-            else {
-                /* Client send zero bytes with C-L > 0
-                 */
-                return HTTP_BAD_REQUEST;
-            }
+            /*
+             * We can only get here if the client closed the connection
+             * to us without sending the body.
+             * Now the connection is in the wrong state on the backend.
+             * Sending an empty data msg doesn't help either as it does
+             * not move this connection to the correct state on the backend
+             * for later resusage by the next request again.
+             * Close it to clean things up.
+             */
+            conn->close++;
+            return HTTP_BAD_REQUEST;
         }
     }
 
     /* read the response */
     conn->data = NULL;
     status = ajp_read_header(conn->sock, r, maxsize,
