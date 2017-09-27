     rv = apr_brigade_vprintf(bb, NULL, NULL, fmt, args);
     va_end(args);
 
     return rv;
 }
 
-static apr_status_t h2_status_stream_filter(h2_stream *stream)
+static void add_settings(apr_bucket_brigade *bb, h2_session *s, int last) 
 {
-    h2_session *session = stream->session;
-    h2_mplx *mplx = session->mplx;
-    conn_rec *c = session->c;
-    h2_push_diary *diary;
-    apr_bucket_brigade *bb;
-    apr_status_t status;
+    h2_mplx *m = s->mplx;
     
-    if (!stream->response) {
-        return APR_EINVAL;
-    }
-    
-    if (!stream->buffer) {
-        stream->buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
-    }
-    bb = stream->buffer;
+    bbout(bb, "  \"settings\": {\n");
+    bbout(bb, "    \"SETTINGS_MAX_CONCURRENT_STREAMS\": %d,\n", m->max_streams); 
+    bbout(bb, "    \"SETTINGS_MAX_FRAME_SIZE\": %d,\n", 16*1024); 
+    bbout(bb, "    \"SETTINGS_INITIAL_WINDOW_SIZE\": %d,\n",
+          h2_config_geti(s->config, H2_CONF_WIN_SIZE));
+    bbout(bb, "    \"SETTINGS_ENABLE_PUSH\": %d\n", h2_session_push_enabled(s)); 
+    bbout(bb, "  }%s\n", last? "" : ",");
+}
+
+static void add_peer_settings(apr_bucket_brigade *bb, h2_session *s, int last) 
+{
+    bbout(bb, "  \"peerSettings\": {\n");
+    bbout(bb, "    \"SETTINGS_MAX_CONCURRENT_STREAMS\": %d,\n", 
+        nghttp2_session_get_remote_settings(s->ngh2, NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS)); 
+    bbout(bb, "    \"SETTINGS_MAX_FRAME_SIZE\": %d,\n", 
+        nghttp2_session_get_remote_settings(s->ngh2, NGHTTP2_SETTINGS_MAX_FRAME_SIZE)); 
+    bbout(bb, "    \"SETTINGS_INITIAL_WINDOW_SIZE\": %d,\n", 
+        nghttp2_session_get_remote_settings(s->ngh2, NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE)); 
+    bbout(bb, "    \"SETTINGS_ENABLE_PUSH\": %d,\n", 
+        nghttp2_session_get_remote_settings(s->ngh2, NGHTTP2_SETTINGS_ENABLE_PUSH)); 
+    bbout(bb, "    \"SETTINGS_HEADER_TABLE_SIZE\": %d,\n", 
+        nghttp2_session_get_remote_settings(s->ngh2, NGHTTP2_SETTINGS_HEADER_TABLE_SIZE)); 
+    bbout(bb, "    \"SETTINGS_MAX_HEADER_LIST_SIZE\": %d\n", 
+        nghttp2_session_get_remote_settings(s->ngh2, NGHTTP2_SETTINGS_MAX_HEADER_LIST_SIZE)); 
+    bbout(bb, "  }%s\n", last? "" : ",");
+}
+
+typedef struct {
+    apr_bucket_brigade *bb;
+    h2_session *s;
+    int idx;
+} stream_ctx_t;
+
+static int add_stream(h2_stream *stream, void *ctx)
+{
+    stream_ctx_t *x = ctx;
+    int32_t flowIn, flowOut;
     
-    apr_table_unset(stream->response->headers, "Content-Length");
-    stream->response->content_length = -1;
+    flowIn = nghttp2_session_get_stream_effective_local_window_size(x->s->ngh2, stream->id); 
+    flowOut = nghttp2_session_get_stream_remote_window_size(x->s->ngh2, stream->id);
+    bbout(x->bb, "%s\n    \"%d\": {\n", (x->idx? "," : ""), stream->id);
+    bbout(x->bb, "    \"state\": \"%s\",\n", h2_stream_state_str(stream));
+    bbout(x->bb, "    \"created\": %f,\n", ((double)stream->created)/APR_USEC_PER_SEC);
+    bbout(x->bb, "    \"flowIn\": %d,\n", flowIn);
+    bbout(x->bb, "    \"flowOut\": %d,\n", flowOut);
+    bbout(x->bb, "    \"dataIn\": %"APR_UINT64_T_FMT",\n", stream->in_data_octets);  
+    bbout(x->bb, "    \"dataOut\": %"APR_UINT64_T_FMT"\n", stream->out_data_octets);  
+    bbout(x->bb, "    }");
+    
+    ++x->idx;
+    return 1;
+} 
+
+static void add_streams(apr_bucket_brigade *bb, h2_session *s, int last) 
+{
+    stream_ctx_t x;
     
-    bbout(bb, "{\n");
-    bbout(bb, "  \"HTTP2\": \"on\",\n");
-    bbout(bb, "  \"H2PUSH\": \"%s\",\n", h2_session_push_enabled(session)? "on" : "off");
-    bbout(bb, "  \"mod_http2_version\": \"%s\",\n", MOD_HTTP2_VERSION);
-    bbout(bb, "  \"session_id\": %ld,\n", (long)session->id);
-    bbout(bb, "  \"streams_max\": %d,\n", (int)session->max_stream_count);
-    bbout(bb, "  \"this_stream\": %d,\n", stream->id);
-    bbout(bb, "  \"streams_open\": %d,\n", (int)h2_ihash_count(session->streams));
-    bbout(bb, "  \"max_stream_started\": %d,\n", mplx->max_stream_started);
-    bbout(bb, "  \"requests_received\": %d,\n", session->remote.emitted_count);
-    bbout(bb, "  \"responses_submitted\": %d,\n", session->responses_submitted);
-    bbout(bb, "  \"streams_reset\": %d, \n", session->streams_reset);
-    bbout(bb, "  \"pushes_promised\": %d,\n", session->pushes_promised);
-    bbout(bb, "  \"pushes_submitted\": %d,\n", session->pushes_submitted);
-    bbout(bb, "  \"pushes_reset\": %d,\n", session->pushes_reset);
+    x.bb = bb;
+    x.s = s;
+    x.idx = 0;
+    bbout(bb, "  \"streams\": {");
+    h2_mplx_stream_do(s->mplx, add_stream, &x);
+    bbout(bb, "\n  }%s\n", last? "" : ",");
+}
+
+static void add_push(apr_bucket_brigade *bb, h2_session *s, 
+                     h2_stream *stream, int last) 
+{
+    h2_push_diary *diary;
+    apr_status_t status;
     
-    diary = session->push_diary;
+    bbout(bb, "    \"push\": {\n");
+    diary = s->push_diary;
     if (diary) {
         const char *data;
         const char *base64_digest;
         apr_size_t len;
         
-        status = h2_push_diary_digest_get(diary, stream->pool, 256, 
-                                          stream->request->authority, &data, &len);
+        status = h2_push_diary_digest_get(diary, bb->p, 256, 
+                                          stream->request->authority, 
+                                          &data, &len);
         if (status == APR_SUCCESS) {
-            base64_digest = h2_util_base64url_encode(data, len, stream->pool);
-            bbout(bb, "  \"cache_digest\": \"%s\",\n", base64_digest);
-        }
-        
-        /* try the reverse for testing purposes */
-        status = h2_push_diary_digest_set(diary, stream->request->authority, data, len);
-        if (status == APR_SUCCESS) {
-            status = h2_push_diary_digest_get(diary, stream->pool, 256, 
-                                              stream->request->authority, &data, &len);
-            if (status == APR_SUCCESS) {
-                base64_digest = h2_util_base64url_encode(data, len, stream->pool);
-                bbout(bb, "  \"cache_digest^2\": \"%s\",\n", base64_digest);
-            }
+            base64_digest = h2_util_base64url_encode(data, len, bb->p);
+            bbout(bb, "      \"cacheDigest\": \"%s\",\n", base64_digest);
         }
     }
-    bbout(bb, "  \"frames_received\": %ld,\n", (long)session->frames_received);
-    bbout(bb, "  \"frames_sent\": %ld,\n", (long)session->frames_sent);
-    bbout(bb, "  \"bytes_received\": %"APR_UINT64_T_FMT",\n", session->io.bytes_read);
-    bbout(bb, "  \"bytes_sent\": %"APR_UINT64_T_FMT"\n", session->io.bytes_written);
+    bbout(bb, "      \"promises\": %d,\n", s->pushes_promised);
+    bbout(bb, "      \"submits\": %d,\n", s->pushes_submitted);
+    bbout(bb, "      \"resets\": %d\n", s->pushes_reset);
+    bbout(bb, "    }%s\n", last? "" : ",");
+}
+
+static void add_in(apr_bucket_brigade *bb, h2_session *s, int last) 
+{
+    bbout(bb, "    \"in\": {\n");
+    bbout(bb, "      \"requests\": %d,\n", s->remote.emitted_count);
+    bbout(bb, "      \"resets\": %d, \n", s->streams_reset);
+    bbout(bb, "      \"frames\": %ld,\n", (long)s->frames_received);
+    bbout(bb, "      \"octets\": %"APR_UINT64_T_FMT"\n", s->io.bytes_read);
+    bbout(bb, "    }%s\n", last? "" : ",");
+}
+
+static void add_out(apr_bucket_brigade *bb, h2_session *s, int last) 
+{
+    bbout(bb, "    \"out\": {\n");
+    bbout(bb, "      \"responses\": %d,\n", s->responses_submitted);
+    bbout(bb, "      \"frames\": %ld,\n", (long)s->frames_sent);
+    bbout(bb, "      \"octets\": %"APR_UINT64_T_FMT"\n", s->io.bytes_written);
+    bbout(bb, "    }%s\n", last? "" : ",");
+}
+
+static void add_stats(apr_bucket_brigade *bb, h2_session *s, 
+                     h2_stream *stream, int last) 
+{
+    bbout(bb, "  \"stats\": {\n");
+    add_in(bb, s, 0);
+    add_out(bb, s, 0);
+    add_push(bb, s, stream, 1);
+    bbout(bb, "  }%s\n", last? "" : ",");
+}
+
+static apr_status_t h2_status_insert(h2_task *task, apr_bucket *b)
+{
+    h2_mplx *m = task->mplx;
+    h2_stream *stream = h2_mplx_stream_get(m, task->stream_id);
+    h2_session *s;
+    conn_rec *c;
+    
+    apr_bucket_brigade *bb;
+    apr_bucket *e;
+    int32_t connFlowIn, connFlowOut;
+    
+    if (!stream) {
+        /* stream already done */
+        return APR_SUCCESS;
+    }
+    s = stream->session;
+    c = s->c;
+    
+    bb = apr_brigade_create(stream->pool, c->bucket_alloc);
+    
+    connFlowIn = nghttp2_session_get_effective_local_window_size(s->ngh2); 
+    connFlowOut = nghttp2_session_get_remote_window_size(s->ngh2);
+     
+    bbout(bb, "{\n");
+    bbout(bb, "  \"version\": \"draft-01\",\n");
+    add_settings(bb, s, 0);
+    add_peer_settings(bb, s, 0);
+    bbout(bb, "  \"connFlowIn\": %d,\n", connFlowIn);
+    bbout(bb, "  \"connFlowOut\": %d,\n", connFlowOut);
+    bbout(bb, "  \"sentGoAway\": %d,\n", s->local.shutdown);
+
+    add_streams(bb, s, 0);
+    
+    add_stats(bb, s, stream, 1);
     bbout(bb, "}\n");
     
+    while ((e = APR_BRIGADE_FIRST(bb)) != APR_BRIGADE_SENTINEL(bb)) {
+        APR_BUCKET_REMOVE(e);
+        APR_BUCKET_INSERT_AFTER(b, e);
+        b = e;
+    }
+    apr_brigade_destroy(bb);
+    
     return APR_SUCCESS;
 }
 
-apr_status_t h2_stream_filter(h2_stream *stream)
+static apr_status_t status_event(void *ctx, h2_bucket_event event, 
+                                 apr_bucket *b)
 {
-    const char *fname = stream->response? stream->response->sos_filter : NULL; 
-    if (fname && !strcmp(H2_SOS_H2_STATUS, fname)) {
-        return h2_status_stream_filter(stream);
+    h2_task *task = ctx;
+    
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, task->c->master, 
+                  "status_event(%s): %d", task->id, event);
+    switch (event) {
+        case H2_BUCKET_EV_BEFORE_MASTER_SEND:
+            h2_status_insert(task, b);
+            break;
+        default:
+            break;
     }
     return APR_SUCCESS;
 }
 
+int h2_filter_h2_status_handler(request_rec *r)
+{
+    h2_ctx *ctx = h2_ctx_rget(r);
+    conn_rec *c = r->connection;
+    h2_task *task;
+    apr_bucket_brigade *bb;
+    apr_bucket *b;
+    apr_status_t status;
+    
+    if (strcmp(r->handler, "http2-status")) {
+        return DECLINED;
+    }
+    if (r->method_number != M_GET && r->method_number != M_POST) {
+        return DECLINED;
+    }
+
+    task = ctx? h2_ctx_get_task(ctx) : NULL;
+    if (task) {
+
+        if ((status = ap_discard_request_body(r)) != OK) {
+            return status;
+        }
+        
+        /* We need to handle the actual output on the main thread, as
+         * we need to access h2_session information. */
+        r->status = 200;
+        r->clength = -1;
+        r->chunked = 1;
+        apr_table_unset(r->headers_out, "Content-Length");
+        ap_set_content_type(r, "application/json");
+        apr_table_setn(r->notes, H2_FILTER_DEBUG_NOTE, "on");
+
+        bb = apr_brigade_create(r->pool, c->bucket_alloc);
+        b = h2_bucket_observer_create(c->bucket_alloc, status_event, task);
+        APR_BRIGADE_INSERT_TAIL(bb, b);
+        b = apr_bucket_eos_create(c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(bb, b);
+
+        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
+                      "status_handler(%s): checking for incoming trailers", 
+                      task->id);
+        if (r->trailers_in && !apr_is_empty_table(r->trailers_in)) {
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
+                          "status_handler(%s): seeing incoming trailers", 
+                          task->id);
+            apr_table_setn(r->trailers_out, "h2-trailers-in", 
+                           apr_itoa(r->pool, 1));
+        }
+        
+        status = ap_pass_brigade(r->output_filters, bb);
+        if (status == APR_SUCCESS
+            || r->status != HTTP_OK
+            || c->aborted) {
+            return OK;
+        }
+        else {
+            /* no way to know what type of error occurred */
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, status, r,
+                          "status_handler(%s): ap_pass_brigade failed", 
+                          task->id);
+            return AP_FILTER_ERROR;
+        }
+    }
+    return DECLINED;
+}
+
