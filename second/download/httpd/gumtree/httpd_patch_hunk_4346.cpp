 
 AP_DECLARE(void) ap_die(int type, request_rec *r)
 {
     ap_die_r(type, r, r->status);
 }
 
-static void check_pipeline(conn_rec *c, apr_bucket_brigade *bb)
+AP_DECLARE(apr_status_t) ap_check_pipeline(conn_rec *c, apr_bucket_brigade *bb,
+                                           unsigned int max_blank_lines)
 {
-    apr_status_t rv;
-    int num_blank_lines = DEFAULT_LIMIT_BLANK_LINES;
+    apr_status_t rv = APR_EOF;
     ap_input_mode_t mode = AP_MODE_SPECULATIVE;
+    unsigned int num_blank_lines = 0;
     apr_size_t cr = 0;
     char buf[2];
 
-    c->data_in_input_filters = 0;
     while (c->keepalive != AP_CONN_CLOSE && !c->aborted) {
         apr_size_t len = cr + 1;
 
         apr_brigade_cleanup(bb);
         rv = ap_get_brigade(c->input_filters, bb, mode,
                             APR_NONBLOCK_READ, len);
-        if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(bb)) {
-            /*
-             * Error or empty brigade: There is no data present in the input
-             * filter
-             */
+        if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(bb) || !max_blank_lines) {
             if (mode == AP_MODE_READBYTES) {
                 /* Unexpected error, stop with this connection */
                 ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(02967)
                               "Can't consume pipelined empty lines");
                 c->keepalive = AP_CONN_CLOSE;
+                rv = APR_EGENERAL;
+            }
+            else if (rv != APR_SUCCESS || APR_BRIGADE_EMPTY(bb)) {
+                if (rv != APR_SUCCESS && !APR_STATUS_IS_EAGAIN(rv)) {
+                    /* Pipe is dead */
+                    c->keepalive = AP_CONN_CLOSE;
+                }
+                else {
+                    /* Pipe is up and empty */
+                    rv = APR_EAGAIN;
+                }
+            }
+            else {
+                apr_off_t n = 0;
+                /* Single read asked, (non-meta-)data available? */
+                rv = apr_brigade_length(bb, 0, &n);
+                if (rv == APR_SUCCESS && n <= 0) {
+                    rv = APR_EAGAIN;
+                }
             }
             break;
         }
 
-        /* Ignore trailing blank lines (which must not be interpreted as
-         * pipelined requests) up to the limit, otherwise we would block
-         * on the next read without flushing data, and hence possibly delay
-         * pending response(s) until the next/real request comes in or the
-         * keepalive timeout expires.
-         */
+        /* Lookup and consume blank lines */
         rv = apr_brigade_flatten(bb, buf, &len);
         if (rv != APR_SUCCESS || len != cr + 1) {
             int log_level;
             if (mode == AP_MODE_READBYTES) {
                 /* Unexpected error, stop with this connection */
                 c->keepalive = AP_CONN_CLOSE;
                 log_level = APLOG_ERR;
+                rv = APR_EGENERAL;
             }
             else {
                 /* Let outside (non-speculative/blocking) read determine
                  * where this possible failure comes from (metadata,
-                 * morphed EOF socket => empty bucket? debug only here).
+                 * morphed EOF socket, ...). Debug only here.
                  */
-                c->data_in_input_filters = 1;
                 log_level = APLOG_DEBUG;
+                rv = APR_SUCCESS;
             }
             ap_log_cerror(APLOG_MARK, log_level, rv, c, APLOGNO(02968)
                           "Can't check pipelined data");
             break;
         }
 
         if (mode == AP_MODE_READBYTES) {
+            /* [CR]LF consumed, try next */
             mode = AP_MODE_SPECULATIVE;
             cr = 0;
         }
         else if (cr) {
             AP_DEBUG_ASSERT(len == 2 && buf[0] == APR_ASCII_CR);
             if (buf[1] == APR_ASCII_LF) {
+                /* consume this CRLF */
                 mode = AP_MODE_READBYTES;
-                num_blank_lines--;
+                num_blank_lines++;
             }
             else {
-                c->data_in_input_filters = 1;
+                /* CR(?!LF) is data */
                 break;
             }
         }
         else {
             if (buf[0] == APR_ASCII_LF) {
+                /* consume this LF */
                 mode = AP_MODE_READBYTES;
-                num_blank_lines--;
+                num_blank_lines++;
             }
             else if (buf[0] == APR_ASCII_CR) {
                 cr = 1;
             }
             else {
-                c->data_in_input_filters = 1;
+                /* Not [CR]LF, some data */
                 break;
             }
         }
-        /* Enough blank lines with this connection?
-         * Stop and don't recycle it.
-         */
-        if (num_blank_lines < 0) {
+        if (num_blank_lines > max_blank_lines) {
+            /* Enough blank lines with this connection,
+             * stop and don't recycle it.
+             */
             c->keepalive = AP_CONN_CLOSE;
+            rv = APR_NOTFOUND;
+            break;
         }
     }
+
+    return rv;
 }
 
 
 AP_DECLARE(void) ap_process_request_after_handler(request_rec *r)
 {
     apr_bucket_brigade *bb;
     apr_bucket *b;
     conn_rec *c = r->connection;
+    apr_status_t rv;
 
     /* Send an EOR bucket through the output filter chain.  When
      * this bucket is destroyed, the request will be logged and
      * its pool will be freed
      */
     bb = apr_brigade_create(c->pool, c->bucket_alloc);
