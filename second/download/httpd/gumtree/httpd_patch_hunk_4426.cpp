         stream->files = NULL;
     }
     return APR_SUCCESS;
 }
 
 h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session,
-                          int initiated_on, const h2_request *creq)
+                          int initiated_on)
 {
-    h2_request *req;
     h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
     
-    stream->id        = id;
-    stream->state     = H2_STREAM_ST_IDLE;
-    stream->pool      = pool;
-    stream->session   = session;
-    set_state(stream, H2_STREAM_ST_OPEN);
+    stream->id           = id;
+    stream->initiated_on = initiated_on;
+    stream->created      = apr_time_now();
+    stream->state        = H2_STREAM_ST_IDLE;
+    stream->pool         = pool;
+    stream->session      = session;
+    stream->can_be_cleaned = 1;
     
-    if (creq) {
-        /* take it into out pool and assure correct id's */
-        req = h2_request_clone(pool, creq);
-        req->id = id;
-        req->initiated_on = initiated_on;
-    }
-    else {
-        req = h2_req_create(id, pool, 
-                h2_config_geti(session->config, H2_CONF_SER_HEADERS));
-    }
-    stream->request = req; 
+    h2_beam_create(&stream->input, pool, id, "input", H2_BEAM_OWNER_SEND, 0);
+    h2_beam_create(&stream->output, pool, id, "output", H2_BEAM_OWNER_RECV, 0);
     
+    set_state(stream, H2_STREAM_ST_OPEN);
     apr_pool_cleanup_register(pool, stream, stream_pool_cleanup, 
                               apr_pool_cleanup_null);
     ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
                   "h2_stream(%ld-%d): opened", session->id, stream->id);
     return stream;
 }
 
 void h2_stream_cleanup(h2_stream *stream)
 {
-    AP_DEBUG_ASSERT(stream);
-    if (stream->buffer) {
-        apr_brigade_cleanup(stream->buffer);
-    }
-    if (stream->input) {
-        apr_status_t status;
-        status = h2_beam_shutdown(stream->input, APR_NONBLOCK_READ, 1);
-        if (status == APR_EAGAIN) {
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
-                          "h2_stream(%ld-%d): wait on input shutdown", 
-                          stream->session->id, stream->id);
-            status = h2_beam_shutdown(stream->input, APR_BLOCK_READ, 1);
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
-                          "h2_stream(%ld-%d): input shutdown returned", 
-                          stream->session->id, stream->id);
-        }
+    apr_status_t status;
+    
+    ap_assert(stream);
+    if (stream->out_buffer) {
+        /* remove any left over output buckets that may still have
+         * references into request pools */
+        apr_brigade_cleanup(stream->out_buffer);
+    }
+    h2_beam_abort(stream->input);
+    status = h2_beam_wait_empty(stream->input, APR_NONBLOCK_READ);
+    if (status == APR_EAGAIN) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c, 
+                      "h2_stream(%ld-%d): wait on input drain", 
+                      stream->session->id, stream->id);
+        status = h2_beam_wait_empty(stream->input, APR_BLOCK_READ);
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c, 
+                      "h2_stream(%ld-%d): input drain returned", 
+                      stream->session->id, stream->id);
     }
 }
 
 void h2_stream_destroy(h2_stream *stream)
 {
-    AP_DEBUG_ASSERT(stream);
+    ap_assert(stream);
+    ap_assert(!h2_mplx_stream_get(stream->session->mplx, stream->id));
     ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, stream->session->c, 
                   "h2_stream(%ld-%d): destroy", 
                   stream->session->id, stream->id);
+    stream->can_be_cleaned = 1;
     if (stream->pool) {
         apr_pool_destroy(stream->pool);
     }
 }
 
 void h2_stream_eos_destroy(h2_stream *stream)
