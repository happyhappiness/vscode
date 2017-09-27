             SSL_do_handshake(ssl);
 
             sslconn->reneg_state = RENEG_REJECT;
 
             if (SSL_get_state(ssl) != SSL_ST_OK) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02261)
-                              "Re-negotiation handshake failed: "
-                              "Not accepted by client!?");
+                              "Re-negotiation handshake failed");
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, r->server);
 
                 r->connection->keepalive = AP_CONN_CLOSE;
                 return HTTP_FORBIDDEN;
             }
         }
 
