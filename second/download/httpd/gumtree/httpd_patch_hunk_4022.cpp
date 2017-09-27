 }
 
 static void update_window(void *ctx, int stream_id, apr_off_t bytes_read)
 {
     h2_session *session = (h2_session*)ctx;
     nghttp2_session_consume(session->ngh2, stream_id, bytes_read);
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                   "h2_session(%ld-%d): consumed %ld bytes",
                   session->id, stream_id, (long)bytes_read);
 }
 
+static apr_status_t h2_session_receive(void *ctx, 
+                                       const char *data, apr_size_t len,
+                                       apr_size_t *readlen);
+
+static int is_accepting_streams(h2_session *session); 
+static void dispatch_event(h2_session *session, h2_session_event_t ev, 
+                             int err, const char *msg);
+
+typedef struct stream_sel_ctx {
+    h2_session *session;
+    h2_stream *candidate;
+} stream_sel_ctx;
+
+static int find_cleanup_stream(void *udata, void *sdata)
+{
+    stream_sel_ctx *ctx = udata;
+    h2_stream *stream = sdata;
+    if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
+        if (!ctx->session->local.accepting
+            && stream->id > ctx->session->local.accepted_max) {
+            ctx->candidate = stream;
+            return 0;
+        }
+    }
+    else {
+        if (!ctx->session->remote.accepting
+            && stream->id > ctx->session->remote.accepted_max) {
+            ctx->candidate = stream;
+            return 0;
+        }
+    }
+    return 1;
+}
+
+static void cleanup_streams(h2_session *session)
+{
+    stream_sel_ctx ctx;
+    ctx.session = session;
+    ctx.candidate = NULL;
+    while (1) {
+        h2_ihash_iter(session->streams, find_cleanup_stream, &ctx);
+        if (ctx.candidate) {
+            h2_session_stream_destroy(session, ctx.candidate);
+            ctx.candidate = NULL;
+        }
+        else {
+            break;
+        }
+    }
+}
 
 h2_stream *h2_session_open_stream(h2_session *session, int stream_id)
 {
     h2_stream * stream;
     apr_pool_t *stream_pool;
-    if (session->aborted) {
-        return NULL;
-    }
     
     if (session->spare) {
         stream_pool = session->spare;
         session->spare = NULL;
     }
     else {
         apr_pool_create(&stream_pool, session->pool);
+        apr_pool_tag(stream_pool, "h2_stream");
     }
     
     stream = h2_stream_open(stream_id, stream_pool, session);
     
-    h2_stream_set_add(session->streams, stream);
-    if (H2_STREAM_CLIENT_INITIATED(stream_id)
-        && stream_id > session->max_stream_received) {
-        session->max_stream_received = stream->id;
+    h2_ihash_add(session->streams, stream);
+    if (H2_STREAM_CLIENT_INITIATED(stream_id)) {
+        if (stream_id > session->remote.emitted_max) {
+            ++session->remote.emitted_count;
+            session->remote.emitted_max = stream->id;
+            session->local.accepted_max = stream->id;
+        }
+    }
+    else {
+        if (stream_id > session->local.emitted_max) {
+            ++session->local.emitted_count;
+            session->remote.emitted_max = stream->id;
+        }
     }
     
     return stream;
 }
 
-#ifdef H2_NG2_STREAM_API
-
 /**
  * Determine the importance of streams when scheduling tasks.
  * - if both stream depend on the same one, compare weights
  * - if one stream is closer to the root, prioritize that one
  * - if both are on the same level, use the weight of their root
  *   level ancestors
