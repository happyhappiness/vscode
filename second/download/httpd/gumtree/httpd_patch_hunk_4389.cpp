 
 typedef struct {
     h2_proxy_session *session;
     h2_proxy_request_done *done;
 } cleanup_iter_ctx;
 
+static int cancel_iter(void *udata, void *val)
+{
+    cleanup_iter_ctx *ctx = udata;
+    h2_proxy_stream *stream = val;
+    nghttp2_submit_rst_stream(ctx->session->ngh2, NGHTTP2_FLAG_NONE,
+                              stream->id, 0);
+    return 1;
+}
+
+void h2_proxy_session_cancel_all(h2_proxy_session *session)
+{
+    if (!h2_proxy_ihash_empty(session->streams)) {
+        cleanup_iter_ctx ctx;
+        ctx.session = session;
+        ctx.done = session->done;
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03366)
+                      "h2_proxy_session(%s): cancel  %d streams",
+                      session->id, (int)h2_proxy_ihash_count(session->streams));
+        h2_proxy_ihash_iter(session->streams, cancel_iter, &ctx);
+        session_shutdown(session, 0, NULL);
+    }
+}
+
 static int done_iter(void *udata, void *val)
 {
     cleanup_iter_ctx *ctx = udata;
     h2_proxy_stream *stream = val;
-    int touched = (!ctx->session->last_stream_id || 
+    int touched = (stream->data_sent || 
                    stream->id <= ctx->session->last_stream_id);
-    ctx->done(ctx->session, stream->r, 0, touched);
+    ctx->done(ctx->session, stream->r, APR_ECONNABORTED, touched);
     return 1;
 }
 
 void h2_proxy_session_cleanup(h2_proxy_session *session, 
                               h2_proxy_request_done *done)
 {
-    if (session->streams && !h2_ihash_empty(session->streams)) {
+    if (!h2_proxy_ihash_empty(session->streams)) {
         cleanup_iter_ctx ctx;
         ctx.session = session;
         ctx.done = done;
         ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03366)
                       "h2_proxy_session(%s): terminated, %d streams unfinished",
-                      session->id, (int)h2_ihash_count(session->streams));
-        h2_ihash_iter(session->streams, done_iter, &ctx);
-        h2_ihash_clear(session->streams);
+                      session->id, (int)h2_proxy_ihash_count(session->streams));
+        h2_proxy_ihash_iter(session->streams, done_iter, &ctx);
+        h2_proxy_ihash_clear(session->streams);
+    }
+}
+
+static int ping_arrived_iter(void *udata, void *val)
+{
+    h2_proxy_stream *stream = val;
+    if (stream->waiting_on_ping) {
+        stream->waiting_on_ping = 0;
+        stream_resume(stream);
+    }
+    return 1;
+}
+
+static void ping_arrived(h2_proxy_session *session)
+{
+    if (!h2_proxy_ihash_empty(session->streams)) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03470)
+                      "h2_proxy_session(%s): ping arrived, unblocking streams",
+                      session->id);
+        h2_proxy_ihash_iter(session->streams, ping_arrived_iter, &session);
     }
 }
 
 typedef struct {
     h2_proxy_session *session;
     conn_rec *c;
