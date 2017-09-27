 int h2_stream_is_suspended(const h2_stream *stream)
 {
     AP_DEBUG_ASSERT(stream);
     return stream->suspended;
 }
 
-apr_status_t h2_stream_out_prepare(h2_stream *stream, 
-                                   apr_off_t *plen, int *peos)
+static apr_status_t fill_buffer(h2_stream *stream, apr_size_t amount)
 {
-    if (stream->rst_error) {
-        *plen = 0;
-        *peos = 1;
+    conn_rec *c = stream->session->c;
+    apr_bucket *b;
+    apr_status_t status;
+    
+    if (!stream->output) {
+        return APR_EOF;
+    }
+    status = h2_beam_receive(stream->output, stream->buffer, 
+                             APR_NONBLOCK_READ, amount);
+    /* The buckets we reveive are using the stream->buffer pool as
+     * lifetime which is exactly what we want since this is stream->pool.
+     *
+     * However: when we send these buckets down the core output filters, the
+     * filter might decide to setaside them into a pool of its own. And it
+     * might decide, after having sent the buckets, to clear its pool.
+     *
+     * This is problematic for file buckets because it then closed the contained
+     * file. Any split off buckets we sent afterwards will result in a 
+     * APR_EBADF.
+     */
+    for (b = APR_BRIGADE_FIRST(stream->buffer);
+         b != APR_BRIGADE_SENTINEL(stream->buffer);
+         b = APR_BUCKET_NEXT(b)) {
+        if (APR_BUCKET_IS_FILE(b)) {
+            apr_bucket_file *f = (apr_bucket_file *)b->data;
+            apr_pool_t *fpool = apr_file_pool_get(f->fd);
+            if (fpool != c->pool) {
+                apr_bucket_setaside(b, c->pool);
+                if (!stream->files) {
+                    stream->files = apr_array_make(stream->pool, 
+                                                   5, sizeof(apr_file_t*));
+                }
+                APR_ARRAY_PUSH(stream->files, apr_file_t*) = f->fd;
+            }
+        }
+    }
+    return status;
+}
+
+apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
+                                    h2_bucket_beam *output)
+{
+    apr_status_t status = APR_SUCCESS;
+    conn_rec *c = stream->session->c;
+    
+    if (!output_open(stream)) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                      "h2_stream(%ld-%d): output closed", 
+                      stream->session->id, stream->id);
         return APR_ECONNRESET;
     }
+    
+    stream->response = response;
+    stream->output = output;
+    stream->buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
+    
+    h2_stream_filter(stream);
+    if (stream->output) {
+        status = fill_buffer(stream, 0);
+    }
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
+                  "h2_stream(%ld-%d): set_response(%d)", 
+                  stream->session->id, stream->id, 
+                  stream->response->http_status);
+    return status;
+}
 
-    AP_DEBUG_ASSERT(stream->sos);
-    return stream->sos->prepare(stream->sos, plen, peos);
+apr_status_t h2_stream_set_error(h2_stream *stream, int http_status)
+{
+    h2_response *response;
+    
+    if (stream->submitted) {
+        return APR_EINVAL;
+    }
+    response = h2_response_die(stream->id, http_status, stream->request, 
+                               stream->pool);
+    return h2_stream_set_response(stream, response, NULL);
 }
 
-apr_status_t h2_stream_readx(h2_stream *stream, 
-                             h2_io_data_cb *cb, void *ctx,
-                             apr_off_t *plen, int *peos)
+static const apr_size_t DATA_CHUNK_SIZE = ((16*1024) - 100 - 9); 
+
+apr_status_t h2_stream_out_prepare(h2_stream *stream,
+                                   apr_off_t *plen, int *peos)
 {
+    conn_rec *c = stream->session->c;
+    apr_status_t status = APR_SUCCESS;
+    apr_off_t requested;
+
     if (stream->rst_error) {
+        *plen = 0;
+        *peos = 1;
         return APR_ECONNRESET;
     }
-    if (!stream->sos) {
-        return APR_EGENERAL;
+
+    if (*plen > 0) {
+        requested = H2MIN(*plen, DATA_CHUNK_SIZE);
+    }
+    else {
+        requested = DATA_CHUNK_SIZE;
     }
-    return stream->sos->readx(stream->sos, cb, ctx, plen, peos);
+    *plen = requested;
+    
+    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_pre");
+    h2_util_bb_avail(stream->buffer, plen, peos);
+    if (!*peos && *plen < requested) {
+        /* try to get more data */
+        status = fill_buffer(stream, (requested - *plen) + DATA_CHUNK_SIZE);
+        if (APR_STATUS_IS_EOF(status)) {
+            apr_bucket *eos = apr_bucket_eos_create(c->bucket_alloc);
+            APR_BRIGADE_INSERT_TAIL(stream->buffer, eos);
+            status = APR_SUCCESS;
+        }
+        else if (status == APR_EAGAIN) {
+            /* did not receive more, it's ok */
+            status = APR_SUCCESS;
+        }
+        *plen = requested;
+        h2_util_bb_avail(stream->buffer, plen, peos);
+    }
+    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_post");
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
+                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d, trailers=%s",
+                  c->id, stream->id, (long)*plen, *peos,
+                  (stream->response && stream->response->trailers)? 
+                  "yes" : "no");
+    if (!*peos && !*plen && status == APR_SUCCESS) {
+        return APR_EAGAIN;
+    }
+    return status;
 }
 
+
 apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                                apr_off_t *plen, int *peos)
 {
+    conn_rec *c = stream->session->c;
+    apr_status_t status = APR_SUCCESS;
+
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
-    if (!stream->sos) {
-        return APR_EGENERAL;
+    status = h2_append_brigade(bb, stream->buffer, plen, peos);
+    if (status == APR_SUCCESS && !*peos && !*plen) {
+        status = APR_EAGAIN;
     }
-    return stream->sos->read_to(stream->sos, bb, plen, peos);
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
+                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
+                  c->id, stream->id, (long)*plen, *peos);
+    return status;
 }
 
+
 int h2_stream_input_is_open(const h2_stream *stream) 
 {
     return input_open(stream);
 }
 
 int h2_stream_needs_submit(const h2_stream *stream)
