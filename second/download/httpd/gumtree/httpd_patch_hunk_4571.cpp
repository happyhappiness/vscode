 #include "h2_task.h"
 #include "h2_ctx.h"
 #include "h2_task.h"
 #include "h2_util.h"
 
 
-static int state_transition[][7] = {
-    /*  ID OP RL RR CI CO CL */
-/*ID*/{  1, 0, 0, 0, 0, 0, 0 },
-/*OP*/{  1, 1, 0, 0, 0, 0, 0 },
-/*RL*/{  0, 0, 1, 0, 0, 0, 0 },
-/*RR*/{  0, 0, 0, 1, 0, 0, 0 },
-/*CI*/{  1, 1, 0, 0, 1, 0, 0 },
-/*CO*/{  1, 1, 0, 0, 0, 1, 0 },
-/*CL*/{  1, 1, 0, 0, 1, 1, 1 },
+static const char *h2_ss_str(h2_stream_state_t state)
+{
+    switch (state) {
+        case H2_SS_IDLE:
+            return "IDLE";
+        case H2_SS_RSVD_L:
+            return "RESERVED_LOCAL";
+        case H2_SS_RSVD_R:
+            return "RESERVED_REMOTE";
+        case H2_SS_OPEN:
+            return "OPEN";
+        case H2_SS_CLOSED_L:
+            return "HALF_CLOSED_LOCAL";
+        case H2_SS_CLOSED_R:
+            return "HALF_CLOSED_REMOTE";
+        case H2_SS_CLOSED:
+            return "CLOSED";
+        case H2_SS_CLEANUP:
+            return "CLEANUP";
+        default:
+            return "UNKNOWN";
+    }
+}
+
+const char *h2_stream_state_str(h2_stream *stream) 
+{
+    return h2_ss_str(stream->state);
+}
+
+/* Abbreviations for stream transit tables */
+#define S_XXX     (-2)                      /* Programming Error */
+#define S_ERR     (-1)                      /* Protocol Error */
+#define S_NOP     (0)                       /* No Change */
+#define S_IDL     (H2_SS_IDL + 1)
+#define S_RS_L    (H2_SS_RSVD_L + 1)
+#define S_RS_R    (H2_SS_RSVD_R + 1)
+#define S_OPEN    (H2_SS_OPEN + 1)
+#define S_CL_L    (H2_SS_CLOSED_L + 1)
+#define S_CL_R    (H2_SS_CLOSED_R + 1)
+#define S_CLS     (H2_SS_CLOSED + 1)
+#define S_CLN     (H2_SS_CLEANUP + 1)
+
+/* state transisitions when certain frame types are sent */
+static int trans_on_send[][H2_SS_MAX] = {
+/*S_IDLE,S_RS_R, S_RS_L, S_OPEN, S_CL_R, S_CL_L, S_CLS,  S_CLN, */        
+{ S_ERR, S_ERR,  S_ERR,  S_NOP,  S_NOP,  S_ERR,  S_NOP,  S_NOP, },/* DATA */ 
+{ S_ERR, S_ERR,  S_CL_R, S_NOP,  S_NOP,  S_ERR,  S_NOP,  S_NOP, },/* HEADERS */ 
+{ S_NOP, S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP, },/* PRIORITY */    
+{ S_CLS, S_CLS,  S_CLS,  S_CLS,  S_CLS,  S_CLS,  S_NOP,  S_NOP, },/* RST_STREAM */ 
+{ S_ERR, S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* SETTINGS */ 
+{ S_RS_L,S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* PUSH_PROMISE */  
+{ S_ERR, S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* PING */ 
+{ S_ERR, S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* GOAWAY */ 
+{ S_NOP, S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP, },/* WINDOW_UPDATE */ 
+{ S_NOP, S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP, },/* CONT */ 
 };
+/* state transisitions when certain frame types are received */
+static int trans_on_recv[][H2_SS_MAX] = {
+/*S_IDLE,S_RS_R, S_RS_L, S_OPEN, S_CL_R, S_CL_L, S_CLS,  S_CLN, */        
+{ S_ERR, S_ERR,  S_ERR,  S_NOP,  S_ERR,  S_NOP,  S_NOP,  S_NOP, },/* DATA */ 
+{ S_OPEN,S_CL_L, S_ERR,  S_NOP,  S_ERR,  S_NOP,  S_NOP,  S_NOP, },/* HEADERS */ 
+{ S_NOP, S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP, },/* PRIORITY */    
+{ S_ERR, S_CLS,  S_CLS,  S_CLS,  S_CLS,  S_CLS,  S_NOP,  S_NOP, },/* RST_STREAM */ 
+{ S_ERR, S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* SETTINGS */ 
+{ S_RS_R,S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* PUSH_PROMISE */  
+{ S_ERR, S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* PING */ 
+{ S_ERR, S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR,  S_ERR, },/* GOAWAY */ 
+{ S_NOP, S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP, },/* WINDOW_UPDATE */ 
+{ S_NOP, S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP,  S_NOP, },/* CONT */ 
+};
+/* state transisitions when certain events happen */
+static int trans_on_event[][H2_SS_MAX] = {
+/*S_IDLE,S_RS_R, S_RS_L, S_OPEN, S_CL_R, S_CL_L, S_CLS,  S_CLN, */        
+{ S_XXX, S_ERR,  S_ERR,  S_CL_L, S_CLS,  S_XXX,  S_XXX,  S_XXX, },/* EV_CLOSED_L*/
+{ S_ERR, S_ERR,  S_ERR,  S_CL_R, S_ERR,  S_CLS,  S_NOP,  S_NOP, },/* EV_CLOSED_R*/
+{ S_CLS, S_CLS,  S_CLS,  S_CLS,  S_CLS,  S_CLS,  S_NOP,  S_NOP, },/* EV_CANCELLED*/
+{ S_NOP, S_XXX,  S_XXX,  S_XXX,  S_XXX,  S_CLS,  S_CLN,  S_XXX, },/* EV_EOS_SENT*/
+};
+
+static int on_map(h2_stream_state_t state, int map[H2_SS_MAX])
+{
+    int op = map[state];
+    switch (op) {
+        case S_XXX:
+        case S_ERR:
+            return op;
+        case S_NOP:
+            return state;
+        default:
+            return op-1;
+    }
+}
+
+static int on_frame(h2_stream_state_t state, int frame_type, 
+                    int frame_map[][H2_SS_MAX], apr_size_t maxlen)
+{
+    ap_assert(frame_type >= 0);
+    ap_assert(state >= 0);
+    if (frame_type >= maxlen) {
+        return state; /* NOP, ignore unknown frame types */
+    }
+    return on_map(state, frame_map[frame_type]);
+}
+
+static int on_frame_send(h2_stream_state_t state, int frame_type)
+{
+    return on_frame(state, frame_type, trans_on_send, H2_ALEN(trans_on_send));
+}
+
+static int on_frame_recv(h2_stream_state_t state, int frame_type)
+{
+    return on_frame(state, frame_type, trans_on_recv, H2_ALEN(trans_on_recv));
+}
+
+static int on_event(h2_stream* stream, h2_stream_event_t ev)
+{
+    if (stream->monitor && stream->monitor->on_event) {
+        stream->monitor->on_event(stream->monitor->ctx, stream, ev);
+    }
+    if (ev < H2_ALEN(trans_on_event)) {
+        return on_map(stream->state, trans_on_event[ev]);
+    }
+    return stream->state;
+}
 
 static void H2_STREAM_OUT_LOG(int lvl, h2_stream *s, const char *tag)
 {
     if (APLOG_C_IS_LEVEL(s->session->c, lvl)) {
         conn_rec *c = s->session->c;
         char buffer[4 * 1024];
-        const char *line = "(null)";
         apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]);
         
         len = h2_util_bb_print(buffer, bmax, tag, "", s->out_buffer);
-        ap_log_cerror(APLOG_MARK, lvl, 0, c, "bb_dump(%s): %s", 
-                      c->log_id, len? buffer : line);
+        ap_log_cerror(APLOG_MARK, lvl, 0, c, 
+                      H2_STRM_MSG(s, "out-buffer(%s)"), len? buffer : "empty");
+    }
+}
+
+static apr_status_t setup_input(h2_stream *stream) {
+    if (stream->input == NULL) {
+        int empty = (stream->input_eof 
+                     && (!stream->in_buffer 
+                         || APR_BRIGADE_EMPTY(stream->in_buffer)));
+        if (!empty) {
+            h2_beam_create(&stream->input, stream->pool, stream->id, 
+                           "input", H2_BEAM_OWNER_SEND, 0, 
+                           stream->session->s->timeout);
+            h2_beam_send_from(stream->input, stream->pool);
+        }
     }
+    return APR_SUCCESS;
 }
 
-static int set_state(h2_stream *stream, h2_stream_state_t state)
+static apr_status_t close_input(h2_stream *stream)
 {
-    int allowed = state_transition[state][stream->state];
-    if (allowed) {
-        stream->state = state;
-        return 1;
+    conn_rec *c = stream->session->c;
+    apr_status_t status = APR_SUCCESS;
+
+    stream->input_eof = 1;
+    if (stream->input && h2_beam_is_closed(stream->input)) {
+        return APR_SUCCESS;
     }
     
-    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c, APLOGNO(03081)
-                  "h2_stream(%ld-%d): invalid state transition from %d to %d", 
-                  stream->session->id, stream->id, stream->state, state);
-    return 0;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                  H2_STRM_MSG(stream, "closing input"));
+    if (stream->rst_error) {
+        return APR_ECONNRESET;
+    }
+    
+    if (stream->trailers && !apr_is_empty_table(stream->trailers)) {
+        apr_bucket *b;
+        h2_headers *r;
+        
+        if (!stream->in_buffer) {
+            stream->in_buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
+        }
+        
+        r = h2_headers_create(HTTP_OK, stream->trailers, NULL, stream->pool);
+        stream->trailers = NULL;        
+        b = h2_bucket_headers_create(c->bucket_alloc, r);
+        APR_BRIGADE_INSERT_TAIL(stream->in_buffer, b);
+        
+        b = apr_bucket_eos_create(c->bucket_alloc);
+        APR_BRIGADE_INSERT_TAIL(stream->in_buffer, b);
+        
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
+                      H2_STRM_MSG(stream, "added trailers"));
+        h2_stream_dispatch(stream, H2_SEV_IN_DATA_PENDING);
+    }
+    if (stream->input) {
+        h2_stream_flush_input(stream);
+        return h2_beam_close(stream->input);
+    }
+    return status;
 }
 
-static int close_input(h2_stream *stream) 
+static apr_status_t close_output(h2_stream *stream)
 {
-    switch (stream->state) {
-        case H2_STREAM_ST_CLOSED_INPUT:
-        case H2_STREAM_ST_CLOSED:
-            return 0; /* ignore, idempotent */
-        case H2_STREAM_ST_CLOSED_OUTPUT:
-            /* both closed now */
-            set_state(stream, H2_STREAM_ST_CLOSED);
-            break;
-        default:
-            /* everything else we jump to here */
-            set_state(stream, H2_STREAM_ST_CLOSED_INPUT);
-            break;
+    if (!stream->output || h2_beam_is_closed(stream->output)) {
+        return APR_SUCCESS;
     }
-    return 1;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                  H2_STRM_MSG(stream, "closing output"));
+    return h2_beam_leave(stream->output);
 }
 
-static int input_closed(h2_stream *stream) 
+static void on_state_enter(h2_stream *stream) 
 {
-    switch (stream->state) {
-        case H2_STREAM_ST_OPEN:
-        case H2_STREAM_ST_CLOSED_OUTPUT:
-            return 0;
-        default:
-            return 1;
+    if (stream->monitor && stream->monitor->on_state_enter) {
+        stream->monitor->on_state_enter(stream->monitor->ctx, stream);
     }
 }
 
-static int close_output(h2_stream *stream) 
+static void on_state_event(h2_stream *stream, h2_stream_event_t ev) 
 {
+    if (stream->monitor && stream->monitor->on_state_event) {
+        stream->monitor->on_state_event(stream->monitor->ctx, stream, ev);
+    }
+}
+
+static void on_state_invalid(h2_stream *stream) 
+{
+    if (stream->monitor && stream->monitor->on_state_invalid) {
+        stream->monitor->on_state_invalid(stream->monitor->ctx, stream);
+    }
+    /* stream got an event/frame invalid in its state */
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                  H2_STRM_MSG(stream, "invalid state event")); 
     switch (stream->state) {
-        case H2_STREAM_ST_CLOSED_OUTPUT:
-        case H2_STREAM_ST_CLOSED:
-            return 0; /* ignore, idempotent */
-        case H2_STREAM_ST_CLOSED_INPUT:
-            /* both closed now */
-            set_state(stream, H2_STREAM_ST_CLOSED);
+        case H2_SS_OPEN:
+        case H2_SS_RSVD_L:
+        case H2_SS_RSVD_R:
+        case H2_SS_CLOSED_L:
+        case H2_SS_CLOSED_R:
+            h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
             break;
         default:
-            /* everything else we jump to here */
-            set_state(stream, H2_STREAM_ST_CLOSED_OUTPUT);
             break;
     }
-    return 1;
 }
 
-static int input_open(const h2_stream *stream) 
+static apr_status_t transit(h2_stream *stream, int new_state)
 {
-    switch (stream->state) {
-        case H2_STREAM_ST_OPEN:
-        case H2_STREAM_ST_CLOSED_OUTPUT:
-            return 1;
-        default:
-            return 0;
+    if (new_state == stream->state) {
+        return APR_SUCCESS;
+    }
+    else if (new_state < 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c, 
+                      H2_STRM_LOG(APLOGNO(03081), stream, "invalid transition"));
+        on_state_invalid(stream);
+        return APR_EINVAL;
     }
+    
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c, 
+                  H2_STRM_MSG(stream, "transit to [%s]"), h2_ss_str(new_state));
+    stream->state = new_state;
+    switch (new_state) {
+        case H2_SS_IDLE:
+            break;
+        case H2_SS_RSVD_L:
+            close_input(stream);
+            break;
+        case H2_SS_RSVD_R:
+            break;
+        case H2_SS_OPEN:
+            break;
+        case H2_SS_CLOSED_L:
+            close_output(stream);
+            break;
+        case H2_SS_CLOSED_R:
+            close_input(stream);
+            break;
+        case H2_SS_CLOSED:
+            close_input(stream);
+            close_output(stream);
+            if (stream->out_buffer) {
+                apr_brigade_cleanup(stream->out_buffer);
+            }
+            break;
+        case H2_SS_CLEANUP:
+            break;
+    }
+    on_state_enter(stream);
+    return APR_SUCCESS;
 }
 
-static int output_open(h2_stream *stream) 
+void h2_stream_set_monitor(h2_stream *stream, h2_stream_monitor *monitor)
 {
-    switch (stream->state) {
-        case H2_STREAM_ST_OPEN:
-        case H2_STREAM_ST_CLOSED_INPUT:
-            return 1;
+    stream->monitor = monitor;
+}
+
+void h2_stream_dispatch(h2_stream *stream, h2_stream_event_t ev)
+{
+    int new_state;
+    
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
+                  H2_STRM_MSG(stream, "dispatch event %d"), ev);
+    new_state = on_event(stream, ev);
+    if (new_state < 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c, 
+                      H2_STRM_LOG(APLOGNO(10002), stream, "invalid event %d"), ev);
+        on_state_invalid(stream);
+        AP_DEBUG_ASSERT(new_state > S_XXX);
+        return;
+    }
+    else if (new_state == stream->state) {
+        /* nop */
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
+                      H2_STRM_MSG(stream, "non-state event %d"), ev);
+        return;
+    }
+    else {
+        on_state_event(stream, ev);
+        transit(stream, new_state);
+    }
+}
+
+static void set_policy_for(h2_stream *stream, h2_request *r) 
+{
+    int enabled = h2_session_push_enabled(stream->session);
+    stream->push_policy = h2_push_policy_determine(r->headers, stream->pool, 
+                                                   enabled);
+    r->serialize = h2_config_geti(stream->session->config, H2_CONF_SER_HEADERS);
+}
+
+apr_status_t h2_stream_send_frame(h2_stream *stream, int ftype, int flags)
+{
+    apr_status_t status = APR_SUCCESS;
+    int new_state, eos = 0;
+
+    new_state = on_frame_send(stream->state, ftype);
+    if (new_state < 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c, 
+                      H2_STRM_MSG(stream, "invalid frame %d send"), ftype);
+        AP_DEBUG_ASSERT(new_state > S_XXX);
+        return transit(stream, new_state);
+    }
+    
+    switch (ftype) {
+        case NGHTTP2_DATA:
+            eos = (flags & NGHTTP2_FLAG_END_STREAM);
+            break;
+            
+        case NGHTTP2_HEADERS:
+            eos = (flags & NGHTTP2_FLAG_END_STREAM);
+            break;
+            
+        case NGHTTP2_PUSH_PROMISE:
+                /* start pushed stream */
+                ap_assert(stream->request == NULL);
+                ap_assert(stream->rtmp != NULL);
+                status = h2_request_end_headers(stream->rtmp, stream->pool, 1);
+                if (status != APR_SUCCESS) {
+                    return status;
+                }
+                set_policy_for(stream, stream->rtmp);
+                stream->request = stream->rtmp;
+                stream->rtmp = NULL;
+            break;
+            
         default:
-            return 0;
+            break;
+    }
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c, 
+                  H2_STRM_MSG(stream, "send frame %d, eos=%d"), ftype, eos);
+    status = transit(stream, new_state);
+    if (status == APR_SUCCESS && eos) {
+        status = transit(stream, on_event(stream, H2_SEV_CLOSED_L));
     }
+    return status;
 }
 
-static void prep_output(h2_stream *stream) {
-    conn_rec *c = stream->session->c;
-    if (!stream->out_buffer) {
-        stream->out_buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
+apr_status_t h2_stream_recv_frame(h2_stream *stream, int ftype, int flags)
+{
+    apr_status_t status = APR_SUCCESS;
+    int new_state, eos = 0;
+
+    new_state = on_frame_recv(stream->state, ftype);
+    if (new_state < 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c, 
+                      H2_STRM_MSG(stream, "invalid frame %d recv"), ftype);
+        AP_DEBUG_ASSERT(new_state > S_XXX);
+        return transit(stream, new_state);
     }
+    
+    switch (ftype) {
+        case NGHTTP2_DATA:
+            eos = (flags & NGHTTP2_FLAG_END_STREAM);
+            break;
+            
+        case NGHTTP2_HEADERS:
+            eos = (flags & NGHTTP2_FLAG_END_STREAM);
+            if (stream->state == H2_SS_OPEN) {
+                /* trailer HEADER */
+                if (!eos) {
+                    h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
+                }
+            }
+            else {
+                /* request HEADER */
+                ap_assert(stream->request == NULL);
+                ap_assert(stream->rtmp != NULL);
+                status = h2_request_end_headers(stream->rtmp, stream->pool, eos);
+                if (status != APR_SUCCESS) {
+                    return status;
+                }
+                set_policy_for(stream, stream->rtmp);
+                stream->request = stream->rtmp;
+                stream->rtmp = NULL;
+            }
+            break;
+            
+        default:
+            break;
+    }
+    status = transit(stream, new_state);
+    if (status == APR_SUCCESS && eos) {
+        status = transit(stream, on_event(stream, H2_SEV_CLOSED_R));
+    }
+    return status;
 }
 
-static void prepend_response(h2_stream *stream, h2_headers *response)
+apr_status_t h2_stream_flush_input(h2_stream *stream)
 {
-    conn_rec *c = stream->session->c;
-    apr_bucket *b;
+    apr_status_t status = APR_SUCCESS;
     
-    prep_output(stream);
-    b = h2_bucket_headers_create(c->bucket_alloc, response);
-    APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
+    if (stream->in_buffer && !APR_BRIGADE_EMPTY(stream->in_buffer)) {
+        setup_input(stream);
+        status = h2_beam_send(stream->input, stream->in_buffer, APR_BLOCK_READ);
+        stream->in_last_write = apr_time_now();
+    }
+    if (stream->input_eof 
+        && stream->input && !h2_beam_is_closed(stream->input)) {
+        status = h2_beam_close(stream->input);
+    }
+    return status;
 }
 
-static apr_status_t stream_pool_cleanup(void *ctx)
+apr_status_t h2_stream_recv_DATA(h2_stream *stream, uint8_t flags,
+                                    const uint8_t *data, size_t len)
 {
-    h2_stream *stream = ctx;
-    apr_status_t status;
+    h2_session *session = stream->session;
+    apr_status_t status = APR_SUCCESS;
     
-    ap_assert(stream->can_be_cleaned);
-    if (stream->files) {
-        apr_file_t *file;
-        int i;
-        for (i = 0; i < stream->files->nelts; ++i) {
-            file = APR_ARRAY_IDX(stream->files, i, apr_file_t*);
-            status = apr_file_close(file);
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, stream->session->c, 
-                          "h2_stream(%ld-%d): destroy, closed file %d", 
-                          stream->session->id, stream->id, i);
+    stream->in_data_frames++;
+    if (len > 0) {
+        if (APLOGctrace3(session->c)) {
+            const char *load = apr_pstrndup(stream->pool, (const char *)data, len);
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, session->c,
+                          H2_STRM_MSG(stream, "recv DATA, len=%d: -->%s<--"), 
+                          (int)len, load);
         }
-        stream->files = NULL;
+        else {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c,
+                          H2_STRM_MSG(stream, "recv DATA, len=%d"), (int)len);
+        }
+        stream->in_data_octets += len;
+        if (!stream->in_buffer) {
+            stream->in_buffer = apr_brigade_create(stream->pool, 
+                                                   session->c->bucket_alloc);
+        }
+        apr_brigade_write(stream->in_buffer, NULL, NULL, (const char *)data, len);
+        h2_stream_dispatch(stream, H2_SEV_IN_DATA_PENDING);
+    }
+    return status;
+}
+
+static void prep_output(h2_stream *stream) {
+    conn_rec *c = stream->session->c;
+    if (!stream->out_buffer) {
+        stream->out_buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
     }
-    return APR_SUCCESS;
 }
 
-h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session,
-                          int initiated_on)
+h2_stream *h2_stream_create(int id, apr_pool_t *pool, h2_session *session,
+                            h2_stream_monitor *monitor, int initiated_on)
 {
     h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
     
     stream->id           = id;
     stream->initiated_on = initiated_on;
     stream->created      = apr_time_now();
-    stream->state        = H2_STREAM_ST_IDLE;
+    stream->state        = H2_SS_IDLE;
     stream->pool         = pool;
     stream->session      = session;
-    stream->can_be_cleaned = 1;
+    stream->monitor      = monitor;
+    stream->max_mem      = session->max_stream_mem;
     
-    h2_beam_create(&stream->input, pool, id, "input", H2_BEAM_OWNER_SEND, 0);
-    h2_beam_create(&stream->output, pool, id, "output", H2_BEAM_OWNER_RECV, 0);
-    
-    set_state(stream, H2_STREAM_ST_OPEN);
-    apr_pool_cleanup_register(pool, stream, stream_pool_cleanup, 
-                              apr_pool_cleanup_null);
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
-                  "h2_stream(%ld-%d): opened", session->id, stream->id);
+#ifdef H2_NG2_LOCAL_WIN_SIZE
+    stream->in_window_size = 
+        nghttp2_session_get_stream_local_window_size(
+            stream->session->ngh2, stream->id);
+#endif
+
+    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
+                  H2_STRM_LOG(APLOGNO(03082), stream, "created"));
+    on_state_enter(stream);
     return stream;
 }
 
 void h2_stream_cleanup(h2_stream *stream)
 {
     apr_status_t status;
