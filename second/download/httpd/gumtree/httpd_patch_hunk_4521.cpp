 
 #include "h2_filter.h"
 
 #define UNSET       -1
 #define H2MIN(x,y) ((x) < (y) ? (x) : (y))
 
-static apr_status_t consume_brigade(h2_filter_cin *cin, 
-                                    apr_bucket_brigade *bb, 
-                                    apr_read_type_e block)
+static apr_status_t recv_RAW_DATA(conn_rec *c, h2_filter_cin *cin, 
+                                  apr_bucket *b, apr_read_type_e block)
 {
+    h2_session *session = cin->session;
     apr_status_t status = APR_SUCCESS;
-    apr_size_t readlen = 0;
+    apr_size_t len;
+    const char *data;
+    ssize_t n;
     
-    while (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
+    status = apr_bucket_read(b, &data, &len, block);
+    
+    while (status == APR_SUCCESS && len > 0) {
+        n = nghttp2_session_mem_recv(session->ngh2, (const uint8_t *)data, len);
         
-        apr_bucket* bucket = APR_BRIGADE_FIRST(bb);
-        if (APR_BUCKET_IS_METADATA(bucket)) {
-            /* we do nothing regarding any meta here */
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
+                      H2_SSSN_MSG(session, "fed %ld bytes to nghttp2, %ld read"),
+                      (long)len, (long)n);
+        if (n < 0) {
+            if (nghttp2_is_fatal((int)n)) {
+                h2_session_event(session, H2_SESSION_EV_PROTO_ERROR, 
+                                 (int)n, nghttp2_strerror((int)n));
+                status = APR_EGENERAL;
+            }
         }
         else {
-            const char *bucket_data = NULL;
-            apr_size_t bucket_length = 0;
-            status = apr_bucket_read(bucket, &bucket_data,
-                                     &bucket_length, block);
-            
-            if (status == APR_SUCCESS && bucket_length > 0) {
-                apr_size_t consumed = 0;
-
-                status = cin->cb(cin->cb_ctx, bucket_data, bucket_length, &consumed);
-                if (status == APR_SUCCESS && bucket_length > consumed) {
-                    /* We have data left in the bucket. Split it. */
-                    status = apr_bucket_split(bucket, consumed);
-                }
-                readlen += consumed;
-                cin->start_read = apr_time_now();
+            session->io.bytes_read += n;
+            if (len <= n) {
+                break;
             }
+            len -= n;
+            data += n;
         }
-        apr_bucket_delete(bucket);
     }
     
-    if (readlen == 0 && status == APR_SUCCESS && block == APR_NONBLOCK_READ) {
+    return status;
+}
+
+static apr_status_t recv_RAW_brigade(conn_rec *c, h2_filter_cin *cin, 
+                                     apr_bucket_brigade *bb, 
+                                     apr_read_type_e block)
+{
+    apr_status_t status = APR_SUCCESS;
+    apr_bucket* b;
+    int consumed = 0;
+    
+    h2_util_bb_log(c, c->id, APLOG_TRACE2, "RAW_in", bb);
+    while (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
+        b = APR_BRIGADE_FIRST(bb);
+
+        if (APR_BUCKET_IS_METADATA(b)) {
+            /* nop */
+        }
+        else {
+            status = recv_RAW_DATA(c, cin, b, block);
+        }
+        consumed = 1;
+        apr_bucket_delete(b);
+    }
+    
+    if (!consumed && status == APR_SUCCESS && block == APR_NONBLOCK_READ) {
         return APR_EAGAIN;
     }
     return status;
 }
 
-h2_filter_cin *h2_filter_cin_create(apr_pool_t *p, h2_filter_cin_cb *cb, void *ctx)
+h2_filter_cin *h2_filter_cin_create(h2_session *session)
 {
     h2_filter_cin *cin;
     
-    cin = apr_pcalloc(p, sizeof(*cin));
-    cin->pool      = p;
-    cin->cb        = cb;
-    cin->cb_ctx    = ctx;
-    cin->start_read = UNSET;
+    cin = apr_pcalloc(session->pool, sizeof(*cin));
+    if (!cin) {
+        return NULL;
+    }
+    cin->session = session;
     return cin;
 }
 
 void h2_filter_cin_timeout_set(h2_filter_cin *cin, apr_interval_time_t timeout)
 {
     cin->timeout = timeout;
