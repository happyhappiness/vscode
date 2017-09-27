             conn_rec *c = r->connection;
             ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r, APLOGNO(02608)
                           "read request body failed to %pI (%s)"
                           " from %s (%s)", p_conn->addr,
                           p_conn->hostname ? p_conn->hostname: "",
                           c->client_ip, c->remote_host ? c->remote_host: "");
-            return HTTP_BAD_REQUEST;
+            return ap_map_http_request_error(status, HTTP_BAD_REQUEST);
         }
     }
 
     if (header_brigade) {
         /* we never sent the header brigade because there was no request body;
          * send it now
