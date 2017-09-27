 {
     ap_die_r(type, r, r->status);
 }
 
 static void check_pipeline(conn_rec *c, apr_bucket_brigade *bb)
 {
-    if (c->keepalive != AP_CONN_CLOSE && !c->aborted) {
-        apr_status_t rv;
+    apr_status_t rv;
+    int num_blank_lines = DEFAULT_LIMIT_BLANK_LINES;
+    ap_input_mode_t mode = AP_MODE_SPECULATIVE;
+    apr_size_t cr = 0;
+    char buf[2];
 
-        AP_DEBUG_ASSERT(APR_BRIGADE_EMPTY(bb));
-        rv = ap_get_brigade(c->input_filters, bb, AP_MODE_SPECULATIVE,
-                            APR_NONBLOCK_READ, 1);
+    c->data_in_input_filters = 0;
+    while (c->keepalive != AP_CONN_CLOSE && !c->aborted) {
+        apr_size_t len = cr + 1;
+
+        apr_brigade_cleanup(bb);
+        rv = ap_get_brigade(c->input_filters, bb, mode,
+                            APR_NONBLOCK_READ, len);
         if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(bb)) {
             /*
              * Error or empty brigade: There is no data present in the input
              * filter
              */
-            c->data_in_input_filters = 0;
+            if (mode == AP_MODE_READBYTES) {
+                /* Unexpected error, stop with this connection */
+                ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(02967)
+                              "Can't consume pipelined empty lines");
+                c->keepalive = AP_CONN_CLOSE;
+            }
+            break;
+        }
+
+        /* Ignore trailing blank lines (which must not be interpreted as
+         * pipelined requests) up to the limit, otherwise we would block
+         * on the next read without flushing data, and hence possibly delay
+         * pending response(s) until the next/real request comes in or the
+         * keepalive timeout expires.
+         */
+        rv = apr_brigade_flatten(bb, buf, &len);
+        if (rv != APR_SUCCESS || len != cr + 1) {
+            int log_level;
+            if (mode == AP_MODE_READBYTES) {
+                /* Unexpected error, stop with this connection */
+                c->keepalive = AP_CONN_CLOSE;
+                log_level = APLOG_ERR;
+            }
+            else {
+                /* Let outside (non-speculative/blocking) read determine
+                 * where this possible failure comes from (metadata,
+                 * morphed EOF socket => empty bucket? debug only here).
+                 */
+                c->data_in_input_filters = 1;
+                log_level = APLOG_DEBUG;
+            }
+            ap_log_cerror(APLOG_MARK, log_level, rv, c, APLOGNO(02968)
+                          "Can't check pipelined data");
+            break;
+        }
+
+        if (mode == AP_MODE_READBYTES) {
+            mode = AP_MODE_SPECULATIVE;
+            cr = 0;
+        }
+        else if (cr) {
+            AP_DEBUG_ASSERT(len == 2 && buf[0] == APR_ASCII_CR);
+            if (buf[1] == APR_ASCII_LF) {
+                mode = AP_MODE_READBYTES;
+                num_blank_lines--;
+            }
+            else {
+                c->data_in_input_filters = 1;
+                break;
+            }
         }
         else {
-            c->data_in_input_filters = 1;
+            if (buf[0] == APR_ASCII_LF) {
+                mode = AP_MODE_READBYTES;
+                num_blank_lines--;
+            }
+            else if (buf[0] == APR_ASCII_CR) {
+                cr = 1;
+            }
+            else {
+                c->data_in_input_filters = 1;
+                break;
+            }
+        }
+        /* Enough blank lines with this connection?
+         * Stop and don't recycle it.
+         */
+        if (num_blank_lines < 0) {
+            c->keepalive = AP_CONN_CLOSE;
         }
     }
 }
 
 
 AP_DECLARE(void) ap_process_request_after_handler(request_rec *r)
