 
 void h2_stream_rst(h2_stream *stream, int error_code)
 {
     stream->rst_error = error_code;
     close_input(stream);
     close_output(stream);
+    if (stream->out_buffer) {
+        apr_brigade_cleanup(stream->out_buffer);
+    }
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                   "h2_stream(%ld-%d): reset, error=%d", 
                   stream->session->id, stream->id, error_code);
 }
 
-struct h2_response *h2_stream_get_response(h2_stream *stream)
-{
-    return stream->response;
-}
-
-apr_status_t h2_stream_set_request(h2_stream *stream, request_rec *r)
+apr_status_t h2_stream_set_request_rec(h2_stream *stream, request_rec *r)
 {
+    h2_request *req;
     apr_status_t status;
-    AP_DEBUG_ASSERT(stream);
+
+    ap_assert(stream->request == NULL);
+    ap_assert(stream->rtmp == NULL);
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
-    set_state(stream, H2_STREAM_ST_OPEN);
-    status = h2_request_rwrite(stream->request, stream->pool, r);
-    stream->request->serialize = h2_config_geti(h2_config_rget(r), 
-                                                H2_CONF_SER_HEADERS);
+    status = h2_request_rcreate(&req, stream->pool, r);
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
-                  "h2_request(%d): rwrite %s host=%s://%s%s",
-                  stream->request->id, stream->request->method, 
-                  stream->request->scheme, stream->request->authority, 
-                  stream->request->path);
-
+                  "h2_request(%d): set_request_rec %s host=%s://%s%s",
+                  stream->id, req->method, req->scheme, req->authority, 
+                  req->path);
+    stream->rtmp = req;
     return status;
 }
 
+apr_status_t h2_stream_set_request(h2_stream *stream, const h2_request *r)
+{
+    ap_assert(stream->request == NULL);
+    ap_assert(stream->rtmp == NULL);
+    stream->rtmp = h2_request_clone(stream->pool, r);
+    return APR_SUCCESS;
+}
+
+static apr_status_t add_trailer(h2_stream *stream,
+                                const char *name, size_t nlen,
+                                const char *value, size_t vlen)
+{
+    conn_rec *c = stream->session->c;
+    char *hname, *hvalue;
+
+    if (nlen == 0 || name[0] == ':') {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, APR_EINVAL, c, APLOGNO(03060)
+                      "h2_request(%ld-%d): pseudo header in trailer",
+                      c->id, stream->id);
+        return APR_EINVAL;
+    }
+    if (h2_req_ignore_trailer(name, nlen)) {
+        return APR_SUCCESS;
+    }
+    if (!stream->trailers) {
+        stream->trailers = apr_table_make(stream->pool, 5);
+    }
+    hname = apr_pstrndup(stream->pool, name, nlen);
+    hvalue = apr_pstrndup(stream->pool, value, vlen);
+    h2_util_camel_case_header(hname, nlen);
+    apr_table_mergen(stream->trailers, hname, hvalue);
+    
+    return APR_SUCCESS;
+}
+
 apr_status_t h2_stream_add_header(h2_stream *stream,
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
 {
-    AP_DEBUG_ASSERT(stream);
-    if (!stream->response) {
-        if (name[0] == ':') {
-            if ((vlen) > stream->session->s->limit_req_line) {
-                /* pseudo header: approximation of request line size check */
-                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                              "h2_stream(%ld-%d): pseudo header %s too long", 
-                              stream->session->id, stream->id, name);
-                return h2_stream_set_error(stream, 
-                                           HTTP_REQUEST_URI_TOO_LARGE);
-            }
-        }
-        else if ((nlen + 2 + vlen) > stream->session->s->limit_req_fieldsize) {
-            /* header too long */
+    int error = 0;
+    ap_assert(stream);
+    
+    if (stream->has_response) {
+        return APR_EINVAL;    
+    }
+    ++stream->request_headers_added;
+    if (name[0] == ':') {
+        if ((vlen) > stream->session->s->limit_req_line) {
+            /* pseudo header: approximation of request line size check */
             ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                          "h2_stream(%ld-%d): header %s too long", 
+                          "h2_stream(%ld-%d): pseudo header %s too long", 
                           stream->session->id, stream->id, name);
-            return h2_stream_set_error(stream, 
-                                       HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
+            error = HTTP_REQUEST_URI_TOO_LARGE;
         }
-        
-        if (name[0] != ':') {
-            ++stream->request_headers_added;
-            if (stream->request_headers_added 
-                > stream->session->s->limit_req_fields) {
-                /* too many header lines */
-                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                              "h2_stream(%ld-%d): too many header lines", 
-                              stream->session->id, stream->id);
-                return h2_stream_set_error(stream, 
-                                           HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE);
-            }
+    }
+    else if ((nlen + 2 + vlen) > stream->session->s->limit_req_fieldsize) {
+        /* header too long */
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                      "h2_stream(%ld-%d): header %s too long", 
+                      stream->session->id, stream->id, name);
+        error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
+    }
+    
+    if (stream->request_headers_added 
+        > stream->session->s->limit_req_fields + 4) {
+        /* too many header lines, include 4 pseudo headers */
+        if (stream->request_headers_added 
+            > stream->session->s->limit_req_fields + 4 + 100) {
+            /* yeah, right */
+            return APR_ECONNRESET;
         }
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                      "h2_stream(%ld-%d): too many header lines", 
+                      stream->session->id, stream->id);
+        error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
     }
     
     if (h2_stream_is_scheduled(stream)) {
-        return h2_request_add_trailer(stream->request, stream->pool,
-                                      name, nlen, value, vlen);
+        return add_trailer(stream, name, nlen, value, vlen);
+    }
+    else if (error) {
+        return h2_stream_set_error(stream, error); 
     }
     else {
-        if (!input_open(stream)) {
+        if (!stream->rtmp) {
+            stream->rtmp = h2_req_create(stream->id, stream->pool, 
+                                         NULL, NULL, NULL, NULL, NULL, 0);
+        }
+        if (stream->state != H2_STREAM_ST_OPEN) {
             return APR_ECONNRESET;
         }
-        return h2_request_add_header(stream->request, stream->pool,
+        return h2_request_add_header(stream->rtmp, stream->pool,
                                      name, nlen, value, vlen);
     }
 }
 
 apr_status_t h2_stream_schedule(h2_stream *stream, int eos, int push_enabled, 
                                 h2_stream_pri_cmp *cmp, void *ctx)
 {
-    apr_status_t status;
-    AP_DEBUG_ASSERT(stream);
-    AP_DEBUG_ASSERT(stream->session);
-    AP_DEBUG_ASSERT(stream->session->mplx);
-    
-    if (!output_open(stream)) {
-        return APR_ECONNRESET;
-    }
-    if (stream->scheduled) {
-        return APR_EINVAL;
-    }
-    if (eos) {
-        close_input(stream);
-    }
-    
-    if (stream->response) {
-        /* already have a resonse, probably a HTTP error code */
-        return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
-    }
-    
-    /* Seeing the end-of-headers, we have everything we need to 
-     * start processing it.
-     */
-    status = h2_request_end_headers(stream->request, stream->pool, 
-                                    eos, push_enabled);
-    if (status == APR_SUCCESS) {
-        stream->request->body = !eos;
-        stream->scheduled = 1;
-        stream->input_remaining = stream->request->content_length;
-        
-        status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                      "h2_stream(%ld-%d): scheduled %s %s://%s%s",
-                      stream->session->id, stream->id,
-                      stream->request->method, stream->request->scheme,
-                      stream->request->authority, stream->request->path);
-    }
-    else {
-        h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                      "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
-                      stream->session->id, stream->id,
-                      stream->request->method, stream->request->scheme,
-                      stream->request->authority, stream->request->path);
+    apr_status_t status = APR_EINVAL;
+    ap_assert(stream);
+    ap_assert(stream->session);
+    ap_assert(stream->session->mplx);
+    
+    if (!stream->scheduled) {
+        if (eos) {
+            close_input(stream);
+        }
+
+        if (h2_stream_is_ready(stream)) {
+            /* already have a resonse, probably a HTTP error code */
+            return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
+        }
+        else if (!stream->request && stream->rtmp) {
+            /* This is the common case: a h2_request was being assembled, now
+             * it gets finalized and checked for completness */
+            status = h2_request_end_headers(stream->rtmp, stream->pool, eos);
+            if (status == APR_SUCCESS) {
+                stream->rtmp->serialize = h2_config_geti(stream->session->config,
+                                                         H2_CONF_SER_HEADERS); 
+
+                stream->request = stream->rtmp;
+                stream->rtmp = NULL;
+                stream->scheduled = 1;
+                
+                stream->push_policy = h2_push_policy_determine(stream->request->headers, 
+                                                               stream->pool, push_enabled);
+            
+                
+                status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                              "h2_stream(%ld-%d): scheduled %s %s://%s%s "
+                              "chunked=%d",
+                              stream->session->id, stream->id,
+                              stream->request->method, stream->request->scheme,
+                              stream->request->authority, stream->request->path,
+                              stream->request->chunked);
+                return status;
+            }
+        }
+        else {
+            status = APR_ECONNRESET;
+        }
     }
     
+    h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
+                  "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
+                  stream->session->id, stream->id,
+                  stream->request->method, stream->request->scheme,
+                  stream->request->authority, stream->request->path);
     return status;
 }
 
 int h2_stream_is_scheduled(const h2_stream *stream)
 {
     return stream->scheduled;
 }
 
 apr_status_t h2_stream_close_input(h2_stream *stream)
 {
-    apr_status_t status = APR_SUCCESS;
-    
-    AP_DEBUG_ASSERT(stream);
+    conn_rec *c = stream->session->c;
+    apr_status_t status;
+    apr_bucket_brigade *tmp;
+    apr_bucket *b;
+
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                   "h2_stream(%ld-%d): closing input",
                   stream->session->id, stream->id);
-                  
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
     
-    if (close_input(stream) && stream->input) {
-        status = h2_beam_close(stream->input);
+    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
+    if (stream->trailers && !apr_is_empty_table(stream->trailers)) {
+        h2_headers *r = h2_headers_create(HTTP_OK, stream->trailers, 
+                                          NULL, stream->pool);
+        b = h2_bucket_headers_create(c->bucket_alloc, r);
+        APR_BRIGADE_INSERT_TAIL(tmp, b);
+        stream->trailers = NULL;
     }
+    
+    b = apr_bucket_eos_create(c->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(tmp, b);
+    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
+    apr_brigade_destroy(tmp);
     return status;
 }
 
 apr_status_t h2_stream_write_data(h2_stream *stream,
                                   const char *data, size_t len, int eos)
 {
     conn_rec *c = stream->session->c;
     apr_status_t status = APR_SUCCESS;
+    apr_bucket_brigade *tmp;
     
-    AP_DEBUG_ASSERT(stream);
+    ap_assert(stream);
     if (!stream->input) {
         return APR_EOF;
     }
-    if (input_closed(stream) || !stream->request->eoh) {
+    if (input_closed(stream) || !stream->request) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                       "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                       stream->session->id, stream->id, input_closed(stream),
-                      stream->request->eoh);
+                      stream->request != NULL);
         return APR_EINVAL;
     }
 
     ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                   "h2_stream(%ld-%d): add %ld input bytes", 
                   stream->session->id, stream->id, (long)len);
-
-    if (!stream->request->chunked) {
-        stream->input_remaining -= len;
-        if (stream->input_remaining < 0) {
-            ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
-                          APLOGNO(02961) 
-                          "h2_stream(%ld-%d): got %ld more content bytes than announced "
-                          "in content-length header: %ld", 
-                          stream->session->id, stream->id,
-                          (long)stream->request->content_length, 
-                          -(long)stream->input_remaining);
-            h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
-            return APR_ECONNABORTED;
-        }
-    }
     
-    if (!stream->tmp) {
-        stream->tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
-    }
-    apr_brigade_write(stream->tmp, NULL, NULL, data, len);
+    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
+    apr_brigade_write(tmp, NULL, NULL, data, len);
+    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
+    apr_brigade_destroy(tmp);
+    
+    stream->in_data_frames++;
+    stream->in_data_octets += len;
+    
     if (eos) {
-        APR_BRIGADE_INSERT_TAIL(stream->tmp, 
-                                apr_bucket_eos_create(c->bucket_alloc)); 
-        close_input(stream);
+        return h2_stream_close_input(stream);
     }
     
-    status = h2_beam_send(stream->input, stream->tmp, APR_BLOCK_READ);
-    apr_brigade_cleanup(stream->tmp);
     return status;
 }
 
-void h2_stream_set_suspended(h2_stream *stream, int suspended)
-{
-    AP_DEBUG_ASSERT(stream);
-    stream->suspended = !!suspended;
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
-                  "h2_stream(%ld-%d): suspended=%d",
-                  stream->session->id, stream->id, stream->suspended);
-}
-
-int h2_stream_is_suspended(const h2_stream *stream)
-{
-    AP_DEBUG_ASSERT(stream);
-    return stream->suspended;
-}
-
 static apr_status_t fill_buffer(h2_stream *stream, apr_size_t amount)
 {
     conn_rec *c = stream->session->c;
     apr_bucket *b;
     apr_status_t status;
     
     if (!stream->output) {
         return APR_EOF;
     }
-    status = h2_beam_receive(stream->output, stream->buffer, 
+    status = h2_beam_receive(stream->output, stream->out_buffer, 
                              APR_NONBLOCK_READ, amount);
-    /* The buckets we reveive are using the stream->buffer pool as
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c,
+                  "h2_stream(%ld-%d): beam_received",
+                  stream->session->id, stream->id);
+    /* The buckets we reveive are using the stream->out_buffer pool as
      * lifetime which is exactly what we want since this is stream->pool.
      *
      * However: when we send these buckets down the core output filters, the
      * filter might decide to setaside them into a pool of its own. And it
      * might decide, after having sent the buckets, to clear its pool.
      *
      * This is problematic for file buckets because it then closed the contained
      * file. Any split off buckets we sent afterwards will result in a 
      * APR_EBADF.
      */
-    for (b = APR_BRIGADE_FIRST(stream->buffer);
-         b != APR_BRIGADE_SENTINEL(stream->buffer);
+    for (b = APR_BRIGADE_FIRST(stream->out_buffer);
+         b != APR_BRIGADE_SENTINEL(stream->out_buffer);
          b = APR_BUCKET_NEXT(b)) {
         if (APR_BUCKET_IS_FILE(b)) {
             apr_bucket_file *f = (apr_bucket_file *)b->data;
             apr_pool_t *fpool = apr_file_pool_get(f->fd);
             if (fpool != c->pool) {
                 apr_bucket_setaside(b, c->pool);
