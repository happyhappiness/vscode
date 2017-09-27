             }
         }
     }
     return status;
 }
 
-apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
-                                    h2_bucket_beam *output)
+apr_status_t h2_stream_set_error(h2_stream *stream, int http_status)
 {
-    apr_status_t status = APR_SUCCESS;
-    conn_rec *c = stream->session->c;
+    h2_headers *response;
     
-    if (!output_open(stream)) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
-                      "h2_stream(%ld-%d): output closed", 
-                      stream->session->id, stream->id);
-        return APR_ECONNRESET;
-    }
-    
-    stream->response = response;
-    stream->output = output;
-    stream->buffer = apr_brigade_create(stream->pool, c->bucket_alloc);
-    
-    h2_stream_filter(stream);
-    if (stream->output) {
-        status = fill_buffer(stream, 0);
+    if (h2_stream_is_ready(stream)) {
+        return APR_EINVAL;
     }
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
-                  "h2_stream(%ld-%d): set_response(%d)", 
-                  stream->session->id, stream->id, 
-                  stream->response->http_status);
-    return status;
+    if (stream->rtmp) {
+        stream->request = stream->rtmp;
+        stream->rtmp = NULL;
+    }
+    response = h2_headers_die(http_status, stream->request, stream->pool);
+    prepend_response(stream, response);
+    h2_beam_close(stream->output);
+    return APR_SUCCESS;
 }
 
-apr_status_t h2_stream_set_error(h2_stream *stream, int http_status)
+static apr_bucket *get_first_headers_bucket(apr_bucket_brigade *bb)
 {
-    h2_response *response;
-    
-    if (stream->submitted) {
-        return APR_EINVAL;
+    if (bb) {
+        apr_bucket *b = APR_BRIGADE_FIRST(bb);
+        while (b != APR_BRIGADE_SENTINEL(bb)) {
+            if (H2_BUCKET_IS_HEADERS(b)) {
+                return b;
+            }
+            b = APR_BUCKET_NEXT(b);
+        }
     }
-    response = h2_response_die(stream->id, http_status, stream->request, 
-                               stream->pool);
-    return h2_stream_set_response(stream, response, NULL);
+    return NULL;
 }
 
-static const apr_size_t DATA_CHUNK_SIZE = ((16*1024) - 100 - 9); 
-
-apr_status_t h2_stream_out_prepare(h2_stream *stream,
-                                   apr_off_t *plen, int *peos)
+apr_status_t h2_stream_out_prepare(h2_stream *stream, apr_off_t *plen, 
+                                   int *peos, h2_headers **presponse)
 {
     conn_rec *c = stream->session->c;
     apr_status_t status = APR_SUCCESS;
     apr_off_t requested;
+    apr_bucket *b, *e;
 
+    if (presponse) {
+        *presponse = NULL;
+    }
+    
     if (stream->rst_error) {
         *plen = 0;
         *peos = 1;
         return APR_ECONNRESET;
     }
+    
+    if (!output_open(stream)) {
+        return APR_ECONNRESET;
+    }
+    prep_output(stream);
 
     if (*plen > 0) {
-        requested = H2MIN(*plen, DATA_CHUNK_SIZE);
+        requested = H2MIN(*plen, H2_DATA_CHUNK_SIZE);
     }
     else {
-        requested = DATA_CHUNK_SIZE;
+        requested = H2_DATA_CHUNK_SIZE;
     }
     *plen = requested;
     
     H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_pre");
-    h2_util_bb_avail(stream->buffer, plen, peos);
+    h2_util_bb_avail(stream->out_buffer, plen, peos);
     if (!*peos && *plen < requested) {
         /* try to get more data */
-        status = fill_buffer(stream, (requested - *plen) + DATA_CHUNK_SIZE);
+        status = fill_buffer(stream, (requested - *plen) + H2_DATA_CHUNK_SIZE);
         if (APR_STATUS_IS_EOF(status)) {
             apr_bucket *eos = apr_bucket_eos_create(c->bucket_alloc);
-            APR_BRIGADE_INSERT_TAIL(stream->buffer, eos);
+            APR_BRIGADE_INSERT_TAIL(stream->out_buffer, eos);
             status = APR_SUCCESS;
         }
         else if (status == APR_EAGAIN) {
             /* did not receive more, it's ok */
             status = APR_SUCCESS;
         }
         *plen = requested;
-        h2_util_bb_avail(stream->buffer, plen, peos);
+        h2_util_bb_avail(stream->out_buffer, plen, peos);
     }
     H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_post");
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
-                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d, trailers=%s",
-                  c->id, stream->id, (long)*plen, *peos,
-                  (stream->response && stream->response->trailers)? 
-                  "yes" : "no");
-    if (!*peos && !*plen && status == APR_SUCCESS) {
-        return APR_EAGAIN;
+    
+    b = APR_BRIGADE_FIRST(stream->out_buffer);
+    while (b != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
+        e = APR_BUCKET_NEXT(b);
+        if (APR_BUCKET_IS_FLUSH(b)
+            || (!APR_BUCKET_IS_METADATA(b) && b->length == 0)) {
+            APR_BUCKET_REMOVE(b);
+            apr_bucket_destroy(b);
+        }
+        else {
+            break;
+        }
+        b = e;
+    }
+    
+    b = get_first_headers_bucket(stream->out_buffer);
+    if (b) {
+        /* there are HEADERS to submit */
+        *peos = 0;
+        *plen = 0;
+        if (b == APR_BRIGADE_FIRST(stream->out_buffer)) {
+            if (presponse) {
+                *presponse = h2_bucket_headers_get(b);
+                APR_BUCKET_REMOVE(b);
+                apr_bucket_destroy(b);
+                status = APR_SUCCESS;
+            }
+            else {
+                /* someone needs to retrieve the response first */
+                h2_mplx_keep_active(stream->session->mplx, stream->id);
+                status = APR_EAGAIN;
+            }
+        }
+        else {
+            apr_bucket *e = APR_BRIGADE_FIRST(stream->out_buffer);
+            while (e != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
+                if (e == b) {
+                    break;
+                }
+                else if (e->length != (apr_size_t)-1) {
+                    *plen += e->length;
+                }
+                e = APR_BUCKET_NEXT(e);
+            }
+        }
+    }
+    
+    if (!*peos && !*plen && status == APR_SUCCESS 
+        && (!presponse || !*presponse)) {
+        status = APR_EAGAIN;
     }
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
+                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d",
+                  c->id, stream->id, (long)*plen, *peos);
     return status;
 }
 
+static int is_not_headers(apr_bucket *b)
+{
+    return !H2_BUCKET_IS_HEADERS(b);
+}
 
 apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                                apr_off_t *plen, int *peos)
 {
     conn_rec *c = stream->session->c;
     apr_status_t status = APR_SUCCESS;
 
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
-    status = h2_append_brigade(bb, stream->buffer, plen, peos);
+    status = h2_append_brigade(bb, stream->out_buffer, plen, peos, is_not_headers);
     if (status == APR_SUCCESS && !*peos && !*plen) {
         status = APR_EAGAIN;
     }
     ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                   "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                   c->id, stream->id, (long)*plen, *peos);
