 
             if (SSL_get_state(ssl) != SSL_ST_OK) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                              "Re-negotiation handshake failed: "
                         "Not accepted by client!?");
 
+                r->connection->aborted = 1;
                 return HTTP_FORBIDDEN;
             }
         }
 
         /*
          * Remember the peer certificate's DN
