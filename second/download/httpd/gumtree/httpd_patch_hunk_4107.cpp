     ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                   "connection complete to %pI (%s)",
                   nexthop, connectname);
     apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                    backconn->local_addr->port));
 
+
+    bb_back = apr_brigade_create(p, backconn->bucket_alloc);
+
     /* If we are connecting through a remote proxy, we need to pass
      * the CONNECT request on to it.
      */
     if (proxyport) {
     /* FIXME: Error checking ignored.
      */
         ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                       "sending the CONNECT request to the remote proxy");
-        ap_fprintf(backconn->output_filters, bb,
+        ap_fprintf(backconn->output_filters, bb_back,
                    "CONNECT %s HTTP/1.0" CRLF, r->uri);
-        ap_fprintf(backconn->output_filters, bb,
+        ap_fprintf(backconn->output_filters, bb_back,
                    "Proxy-agent: %s" CRLF CRLF, ap_get_server_banner());
-        ap_fflush(backconn->output_filters, bb);
+        ap_fflush(backconn->output_filters, bb_back);
     }
     else {
         ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "Returning 200 OK");
         nbytes = apr_snprintf(buffer, sizeof(buffer),
                               "HTTP/1.0 200 Connection Established" CRLF);
         ap_xlate_proto_to_ascii(buffer, nbytes);
-        ap_fwrite(c->output_filters, bb, buffer, nbytes);
+        ap_fwrite(c->output_filters, bb_front, buffer, nbytes);
         nbytes = apr_snprintf(buffer, sizeof(buffer),
                               "Proxy-agent: %s" CRLF CRLF,
                               ap_get_server_banner());
         ap_xlate_proto_to_ascii(buffer, nbytes);
-        ap_fwrite(c->output_filters, bb, buffer, nbytes);
-        ap_fflush(c->output_filters, bb);
+        ap_fwrite(c->output_filters, bb_front, buffer, nbytes);
+        ap_fflush(c->output_filters, bb_front);
 #if 0
         /* This is safer code, but it doesn't work yet.  I'm leaving it
          * here so that I can fix it later.
          */
         r->status = HTTP_OK;
         r->header_only = 1;
