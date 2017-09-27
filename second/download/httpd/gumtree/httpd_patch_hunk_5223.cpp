     if (cur_timeout != conn->base_server->timeout) {
         apr_socket_timeout_set(csd, conn->base_server->timeout);
         cur_timeout = conn->base_server->timeout;
     }
 
     if (!r->assbackwards) {
+        const char *tenc;
+
         ap_get_mime_headers_core(r, tmp_bb);
         if (r->status != HTTP_OK) {
             ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(00567)
                           "request failed: error reading the headers");
             ap_send_error_response(r, 0);
             ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
             ap_run_log_transaction(r);
             apr_brigade_destroy(tmp_bb);
             goto traceout;
         }
 
-        if (apr_table_get(r->headers_in, "Transfer-Encoding")
-            && apr_table_get(r->headers_in, "Content-Length")) {
-            /* 2616 section 4.4, point 3: "if both Transfer-Encoding
-             * and Content-Length are received, the latter MUST be
-             * ignored"; so unset it here to prevent any confusion
-             * later. */
+        tenc = apr_table_get(r->headers_in, "Transfer-Encoding");
+        if (tenc) {
+            /* http://tools.ietf.org/html/draft-ietf-httpbis-p1-messaging-23
+             * Section 3.3.3.3: "If a Transfer-Encoding header field is
+             * present in a request and the chunked transfer coding is not
+             * the final encoding ...; the server MUST respond with the 400
+             * (Bad Request) status code and then close the connection".
+             */
+            if (!(strcasecmp(tenc, "chunked") == 0 /* fast path */
+                    || ap_find_last_token(r->pool, tenc, "chunked"))) {
+                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02539)
+                              "client sent unknown Transfer-Encoding "
+                              "(%s): %s", tenc, r->uri);
+                r->status = HTTP_BAD_REQUEST;
+                conn->keepalive = AP_CONN_CLOSE;
+                ap_send_error_response(r, 0);
+                ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
+                ap_run_log_transaction(r);
+                apr_brigade_destroy(tmp_bb);
+                goto traceout;
+            }
+
+            /* http://tools.ietf.org/html/draft-ietf-httpbis-p1-messaging-23
+             * Section 3.3.3.3: "If a message is received with both a
+             * Transfer-Encoding and a Content-Length header field, the
+             * Transfer-Encoding overrides the Content-Length. ... A sender
+             * MUST remove the received Content-Length field".
+             */
             apr_table_unset(r->headers_in, "Content-Length");
         }
     }
     else {
         if (r->header_only) {
             /*
