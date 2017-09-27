         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
              "proxy: CONNECT: sending the CONNECT request to the remote proxy");
         nbytes = apr_snprintf(buffer, sizeof(buffer),
                   "CONNECT %s HTTP/1.0" CRLF, r->uri);
         apr_socket_send(sock, buffer, &nbytes);
         nbytes = apr_snprintf(buffer, sizeof(buffer),
-                  "Proxy-agent: %s" CRLF CRLF, ap_get_server_version());
+                  "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
         apr_socket_send(sock, buffer, &nbytes);
     }
     else {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
              "proxy: CONNECT: Returning 200 OK Status");
         nbytes = apr_snprintf(buffer, sizeof(buffer),
                   "HTTP/1.0 200 Connection Established" CRLF);
         ap_xlate_proto_to_ascii(buffer, nbytes);
         apr_socket_send(client_socket, buffer, &nbytes);
         nbytes = apr_snprintf(buffer, sizeof(buffer),
-                  "Proxy-agent: %s" CRLF CRLF, ap_get_server_version());
+                  "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
         ap_xlate_proto_to_ascii(buffer, nbytes);
         apr_socket_send(client_socket, buffer, &nbytes);
 #if 0
         /* This is safer code, but it doesn't work yet.  I'm leaving it
          * here so that I can fix it later.
          */
         r->status = HTTP_OK;
         r->header_only = 1;
-        apr_table_set(r->headers_out, "Proxy-agent: %s", ap_get_server_version());
+        apr_table_set(r->headers_out, "Proxy-agent: %s", ap_get_server_banner());
         ap_rflush(r);
 #endif
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
          "proxy: CONNECT: setting up poll()");
