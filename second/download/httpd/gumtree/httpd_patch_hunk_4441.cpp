                       session->c->remote_host ? session->c->remote_host: "");
     }
     return status;
 }
 
 static void request_done(h2_proxy_session *session, request_rec *r,
-                         int complete, int touched)
+                         apr_status_t status, int touched)
 {   
     h2_proxy_ctx *ctx = session->user_data;
     const char *task_id = apr_table_get(r->connection->notes, H2_TASK_ID_NOTE);
-    
-    if (!complete && !touched) {
-        /* untouched request, need rescheduling */
-        if (req_engine_push && is_h2 && is_h2(ctx->owner)) {
-            if (req_engine_push(ctx->engine_type, r, NULL) == APR_SUCCESS) {
-                /* push to engine */
-                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, 
-                              APLOGNO(03369)
-                              "h2_proxy_session(%s): rescheduled request %s",
-                              ctx->engine_id, task_id);
-                return;
+
+    if (status != APR_SUCCESS) {
+        if (!touched) {
+            /* untouched request, need rescheduling */
+            if (req_engine_push && is_h2 && is_h2(ctx->owner)) {
+                if (req_engine_push(ctx->engine_type, r, NULL) == APR_SUCCESS) {
+                    /* push to engine */
+                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, 
+                                  APLOGNO(03369)
+                                  "h2_proxy_session(%s): rescheduled request %s",
+                                  ctx->engine_id, task_id);
+                    return;
+                }
             }
         }
+        else {
+            const char *uri;
+            uri = apr_uri_unparse(r->pool, &r->parsed_uri, 0);
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
+                          APLOGNO(03471) "h2_proxy_session(%s): request %s -> %s "
+                          "not complete, was touched",
+                          ctx->engine_id, task_id, uri);
+        }
     }
     
-    if (r == ctx->rbase && complete) {
-        ctx->r_status = APR_SUCCESS;
+    if (r == ctx->rbase) {
+        ctx->r_status = (status == APR_SUCCESS)? APR_SUCCESS : HTTP_SERVICE_UNAVAILABLE;
     }
     
-    if (complete) {
-        if (req_engine_done && ctx->engine) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, 
-                          APLOGNO(03370)
-                          "h2_proxy_session(%s): finished request %s",
-                          ctx->engine_id, task_id);
-            req_engine_done(ctx->engine, r->connection);
-        }
-    }
-    else {
-        if (req_engine_done && ctx->engine) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, 
-                          APLOGNO(03371)
-                          "h2_proxy_session(%s): failed request %s",
-                          ctx->engine_id, task_id);
-            req_engine_done(ctx->engine, r->connection);
-        }
+    if (req_engine_done && ctx->engine) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, r->connection, 
+                      APLOGNO(03370)
+                      "h2_proxy_session(%s): finished request %s",
+                      ctx->engine_id, task_id);
+        req_engine_done(ctx->engine, r->connection, status);
     }
 }    
 
 static apr_status_t next_request(h2_proxy_ctx *ctx, int before_leave)
 {
     if (ctx->next) {
