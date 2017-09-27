     return DECLINED;
 }
 
 int h2_h2_process_conn(conn_rec* c)
 {
     h2_ctx *ctx = h2_ctx_get(c);
-    h2_config *cfg = h2_config_get(c);
-    apr_bucket_brigade* temp;
-    int is_tls = h2_h2_is_tls(c);
     
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, process_conn");
     if (h2_ctx_is_task(ctx)) {
         /* our stream pseudo connection */
         return DECLINED;
     }
 
-    /* If we have not already switched to a h2* protocol and the connection 
-     * is on "http/1.1"
-     * -> sniff for the magic PRIamble. On TLS, this might trigger the ALPN.
-     */
-    if (!h2_ctx_protocol_get(c) 
-        && !strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))) {
+    if (h2_ctx_protocol_get(c)) {
+        /* Something has been negotiated */
+    }
+    else if (!strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))
+             && h2_allows_h2_direct(c) 
+             && h2_is_acceptable_connection(c, 1)) {
+        /* connection still is on http/1.1 and H2Direct is enabled. 
+         * Otherwise connection is in a fully acceptable state.
+         * -> peek at the first 24 incoming bytes
+         */
+        apr_bucket_brigade *temp;
         apr_status_t status;
+        char *s = NULL;
+        apr_size_t slen;
         
         temp = apr_brigade_create(c->pool, c->bucket_alloc);
         status = ap_get_brigade(c->input_filters, temp,
                                 AP_MODE_SPECULATIVE, APR_BLOCK_READ, 24);
-
-        if (status == APR_SUCCESS) {
-            if (h2_ctx_protocol_get(c) 
-                || strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))) {
-                /* h2 or another protocol has been selected. */
-            }
-            else {
-                /* ALPN might have been triggered, but we're still on
-                 * http/1.1. Check the actual bytes read for the H2 Magic
-                 * Token, *if* H2Direct mode is enabled here. 
-                 */
-                int direct_mode = h2_config_geti(cfg, H2_CONF_DIRECT);
-                if (direct_mode > 0 || (direct_mode < 0 && !is_tls)) {
-                    char *s = NULL;
-                    apr_size_t slen;
-                    
-                    apr_brigade_pflatten(temp, &s, &slen, c->pool);
-                    if ((slen >= 24) && !memcmp(H2_MAGIC_TOKEN, s, 24)) {
-                        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
-                                      "h2_h2, direct mode detected");
-                        h2_ctx_protocol_set(ctx, is_tls? "h2" : "h2c");
-                    }
-                    else {
-                        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
-                                      "h2_h2, not detected in %d bytes: %s", 
-                                      (int)slen, s);
-                    }
-                }
-            }
-        }
-        else {
+        
+        if (status != APR_SUCCESS) {
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, c,
                           "h2_h2, error reading 24 bytes speculative");
+            apr_brigade_destroy(temp);
+            return DECLINED;
         }
+        
+        apr_brigade_pflatten(temp, &s, &slen, c->pool);
+        if ((slen >= 24) && !memcmp(H2_MAGIC_TOKEN, s, 24)) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                          "h2_h2, direct mode detected");
+            h2_ctx_protocol_set(ctx, h2_h2_is_tls(c)? "h2" : "h2c");
+        }
+        else {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
+                          "h2_h2, not detected in %d bytes: %s", 
+                          (int)slen, s);
+        }
+        
         apr_brigade_destroy(temp);
     }
+    else {
+        /* the connection is not HTTP/1.1 or not for us, don't touch it */
+        return DECLINED;
+    }
 
     /* If "h2" was selected as protocol (by whatever mechanism), take over
      * the connection.
      */
     if (h2_ctx_is_active(ctx)) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                       "h2_h2, connection, h2 active");
         
-        return h2_conn_main(c);
+        return h2_conn_process(c, NULL, ctx->server);
     }
     
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, "h2_h2, declined");
     return DECLINED;
 }
 
 static int h2_h2_post_read_req(request_rec *r)
 {
     h2_ctx *ctx = h2_ctx_rget(r);
-    struct h2_task_env *env = h2_ctx_get_task(ctx);
-    if (env) {
+    struct h2_task *task = h2_ctx_get_task(ctx);
+    if (task) {
+        /* FIXME: sometimes, this hook gets called twice for a single request.
+         * This should not be, right? */
         /* h2_task connection for a stream, not for h2c */
-        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                       "adding h1_to_h2_resp output filter");
-        if (env->serialize_headers) {
+        if (task->serialize_headers) {
             ap_remove_output_filter_byhandle(r->output_filters, "H1_TO_H2_RESP");
-            ap_add_output_filter("H1_TO_H2_RESP", env, r, r->connection);
+            ap_add_output_filter("H1_TO_H2_RESP", task, r, r->connection);
         }
         else {
             /* replace the core http filter that formats response headers
              * in HTTP/1 with our own that collects status and headers */
             ap_remove_output_filter_byhandle(r->output_filters, "HTTP_HEADER");
             ap_remove_output_filter_byhandle(r->output_filters, "H2_RESPONSE");
-            ap_add_output_filter("H2_RESPONSE", env, r, r->connection);
+            ap_add_output_filter("H2_RESPONSE", task, r, r->connection);
         }
+        ap_add_output_filter("H2_TRAILERS", task, r, r->connection);
     }
     return DECLINED;
 }
 
 
