         close_input(stream);
     }
     
     /* Seeing the end-of-headers, we have everything we need to 
      * start processing it.
      */
-    status = h2_request_end_headers(stream->request, stream->pool, eos);
+    status = h2_request_end_headers(stream->request, stream->pool, 
+                                    eos, push_enabled);
     if (status == APR_SUCCESS) {
         if (!eos) {
-            stream->bbin = apr_brigade_create(stream->pool, 
-                                              stream->session->c->bucket_alloc);
+            stream->request->body = 1;
         }
         stream->input_remaining = stream->request->content_length;
         
         status = h2_mplx_process(stream->session->mplx, stream->id, 
-                                 stream->request, eos, cmp, ctx);
+                                 stream->request, cmp, ctx);
         stream->scheduled = 1;
         
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                       "h2_stream(%ld-%d): scheduled %s %s://%s%s",
                       stream->session->id, stream->id,
                       stream->request->method, stream->request->scheme,
                       stream->request->authority, stream->request->path);
     }
     else {
         h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                       "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
                       stream->session->id, stream->id,
                       stream->request->method, stream->request->scheme,
                       stream->request->authority, stream->request->path);
     }
     
     return status;
 }
 
-int h2_stream_is_scheduled(h2_stream *stream)
+int h2_stream_is_scheduled(const h2_stream *stream)
 {
     return stream->scheduled;
 }
 
-static apr_status_t h2_stream_input_flush(h2_stream *stream)
-{
-    apr_status_t status = APR_SUCCESS;
-    if (stream->bbin && !APR_BRIGADE_EMPTY(stream->bbin)) {
-
-        status = h2_mplx_in_write(stream->session->mplx, stream->id, stream->bbin);
-        if (status != APR_SUCCESS) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->session->mplx->c,
-                          "h2_stream(%ld-%d): flushing input data",
-                          stream->session->id, stream->id);
-        }
-    }
-    return status;
-}
-
-static apr_status_t input_flush(apr_bucket_brigade *bb, void *ctx) 
-{
-    (void)bb;
-    return h2_stream_input_flush(ctx);
-}
-
-static apr_status_t input_add_data(h2_stream *stream,
-                                   const char *data, size_t len, int chunked)
-{
-    apr_status_t status = APR_SUCCESS;
-    
-    if (chunked) {
-        status = apr_brigade_printf(stream->bbin, input_flush, stream,
-                                    "%lx\r\n", (unsigned long)len);
-        if (status == APR_SUCCESS) {
-            status = apr_brigade_write(stream->bbin, input_flush, stream, data, len);
-            if (status == APR_SUCCESS) {
-                status = apr_brigade_puts(stream->bbin, input_flush, stream, "\r\n");
-            }
-        }
-    }
-    else {
-        status = apr_brigade_write(stream->bbin, input_flush, stream, data, len);
-    }
-    return status;
-}
-
-static int input_add_header(void *str, const char *key, const char *value)
-{
-    h2_stream *stream = str;
-    apr_status_t status = input_add_data(stream, key, strlen(key), 0);
-    if (status == APR_SUCCESS) {
-        status = input_add_data(stream, ": ", 2, 0);
-        if (status == APR_SUCCESS) {
-            status = input_add_data(stream, value, strlen(value), 0);
-            if (status == APR_SUCCESS) {
-                status = input_add_data(stream, "\r\n", 2, 0);
-            }
-        }
-    }
-    return (status == APR_SUCCESS);
-}
-
 apr_status_t h2_stream_close_input(h2_stream *stream)
 {
     apr_status_t status = APR_SUCCESS;
     
     AP_DEBUG_ASSERT(stream);
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                   "h2_stream(%ld-%d): closing input",
                   stream->session->id, stream->id);
                   
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
     
-    H2_STREAM_IN(APLOG_TRACE2, stream, "close_pre");
-    if (close_input(stream) && stream->bbin) {
-        if (stream->request->chunked) {
-            apr_table_t *trailers = stream->request->trailers;
-            if (trailers && !apr_is_empty_table(trailers)) {
-                status = input_add_data(stream, "0\r\n", 3, 0);
-                apr_table_do(input_add_header, stream, trailers, NULL);
-                status = input_add_data(stream, "\r\n", 2, 0);
-            }
-            else {
-                status = input_add_data(stream, "0\r\n\r\n", 5, 0);
-            }
-        }
-        
-        if (status == APR_SUCCESS) {
-            status = h2_stream_input_flush(stream);
-        }
-        if (status == APR_SUCCESS) {
-            status = h2_mplx_in_close(stream->session->mplx, stream->id);
-        }
+    if (close_input(stream)) {
+        status = h2_mplx_in_close(stream->session->mplx, stream->id);
     }
-    H2_STREAM_IN(APLOG_TRACE2, stream, "close_post");
     return status;
 }
 
 apr_status_t h2_stream_write_data(h2_stream *stream,
-                                  const char *data, size_t len)
+                                  const char *data, size_t len, int eos)
 {
     apr_status_t status = APR_SUCCESS;
     
     AP_DEBUG_ASSERT(stream);
-    if (input_closed(stream) || !stream->request->eoh || !stream->bbin) {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
-                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d, bbin=%d", 
+    if (input_closed(stream) || !stream->request->eoh) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                       stream->session->id, stream->id, input_closed(stream),
-                      stream->request->eoh, !!stream->bbin);
+                      stream->request->eoh);
         return APR_EINVAL;
     }
 
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                   "h2_stream(%ld-%d): add %ld input bytes", 
                   stream->session->id, stream->id, (long)len);
 
-    H2_STREAM_IN(APLOG_TRACE2, stream, "write_data_pre");
-    if (stream->request->chunked) {
-        /* if input may have a body and we have not seen any
-         * content-length header, we need to chunk the input data.
-         */
-        status = input_add_data(stream, data, len, 1);
-    }
-    else {
+    if (!stream->request->chunked) {
         stream->input_remaining -= len;
         if (stream->input_remaining < 0) {
             ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c,
                           APLOGNO(02961) 
                           "h2_stream(%ld-%d): got %ld more content bytes than announced "
                           "in content-length header: %ld", 
                           stream->session->id, stream->id,
                           (long)stream->request->content_length, 
                           -(long)stream->input_remaining);
             h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
             return APR_ECONNABORTED;
         }
-        status = input_add_data(stream, data, len, 0);
     }
-    if (status == APR_SUCCESS) {
-        status = h2_stream_input_flush(stream);
+    
+    status = h2_mplx_in_write(stream->session->mplx, stream->id, data, len, eos);
+    if (eos) {
+        close_input(stream);
     }
-    H2_STREAM_IN(APLOG_TRACE2, stream, "write_data_post");
     return status;
 }
 
-apr_status_t h2_stream_prep_read(h2_stream *stream, 
-                                 apr_off_t *plen, int *peos)
+void h2_stream_set_suspended(h2_stream *stream, int suspended)
+{
+    AP_DEBUG_ASSERT(stream);
+    stream->suspended = !!suspended;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, stream->session->c,
+                  "h2_stream(%ld-%d): suspended=%d",
+                  stream->session->id, stream->id, stream->suspended);
+}
+
+int h2_stream_is_suspended(const h2_stream *stream)
+{
+    AP_DEBUG_ASSERT(stream);
+    return stream->suspended;
+}
+
+apr_status_t h2_stream_out_prepare(h2_stream *stream, 
+                                   apr_off_t *plen, int *peos)
 {
-    apr_status_t status = APR_SUCCESS;
-    const char *src;
-    apr_table_t *trailers = NULL;
-    int test_read = (*plen == 0);
-    
     if (stream->rst_error) {
+        *plen = 0;
+        *peos = 1;
         return APR_ECONNRESET;
     }
 
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream prep_read_pre");
-    if (!APR_BRIGADE_EMPTY(stream->bbout)) {
-        src = "stream";
-        status = h2_util_bb_avail(stream->bbout, plen, peos);
-        if (!test_read && status == APR_SUCCESS && !*peos && !*plen) {
-            apr_brigade_cleanup(stream->bbout);
-            return h2_stream_prep_read(stream, plen, peos);
-        }
-        trailers = stream->response? stream->response->trailers : NULL;
-    }
-    else {
-        src = "mplx";
-        status = h2_mplx_out_readx(stream->session->mplx, stream->id, 
-                                   NULL, NULL, plen, peos, &trailers);
-        if (trailers && stream->response) {
-            h2_response_set_trailers(stream->response, trailers);
-        }    
-    }
-    
-    if (!test_read && status == APR_SUCCESS && !*peos && !*plen) {
-        status = APR_EAGAIN;
-    }
-    
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream prep_read_post");
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                  "h2_stream(%ld-%d): prep_read %s, len=%ld eos=%d, trailers=%s",
-                  stream->session->id, stream->id, src, (long)*plen, *peos,
-                  trailers? "yes" : "no");
-    return status;
+    AP_DEBUG_ASSERT(stream->sos);
+    return stream->sos->prepare(stream->sos, plen, peos);
 }
 
 apr_status_t h2_stream_readx(h2_stream *stream, 
                              h2_io_data_cb *cb, void *ctx,
                              apr_off_t *plen, int *peos)
 {
-    apr_status_t status = APR_SUCCESS;
-    apr_table_t *trailers = NULL;
-    const char *src;
-    
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream readx_pre");
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
-    *peos = 0;
-    if (!APR_BRIGADE_EMPTY(stream->bbout)) {
-        apr_off_t origlen = *plen;
-        
-        src = "stream";
-        status = h2_util_bb_readx(stream->bbout, cb, ctx, plen, peos);
-        if (status == APR_SUCCESS && !*peos && !*plen) {
-            apr_brigade_cleanup(stream->bbout);
-            *plen = origlen;
-            return h2_stream_readx(stream, cb, ctx, plen, peos);
-        }
-    }
-    else {
-        src = "mplx";
-        status = h2_mplx_out_readx(stream->session->mplx, stream->id, 
-                                   cb, ctx, plen, peos, &trailers);
-    }
-    
-    if (trailers && stream->response) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                      "h2_stream(%ld-%d): readx, saving trailers",
-                      stream->session->id, stream->id);
-        h2_response_set_trailers(stream->response, trailers);
-    }
-    
-    if (status == APR_SUCCESS && !*peos && !*plen) {
-        status = APR_EAGAIN;
+    if (!stream->sos) {
+        return APR_EGENERAL;
     }
-    
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream readx_post");
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                  "h2_stream(%ld-%d): readx %s, len=%ld eos=%d",
-                  stream->session->id, stream->id, src, (long)*plen, *peos);
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream readx_post");
-    
-    return status;
+    return stream->sos->readx(stream->sos, cb, ctx, plen, peos);
 }
 
 apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                                apr_off_t *plen, int *peos)
 {
-    apr_status_t status = APR_SUCCESS;
-    apr_table_t *trailers = NULL;
-
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream read_to_pre");
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
-    
-    if (APR_BRIGADE_EMPTY(stream->bbout)) {
-        apr_off_t tlen = *plen;
-        int eos;
-        status = h2_mplx_out_read_to(stream->session->mplx, stream->id, 
-                                     stream->bbout, &tlen, &eos, &trailers);
+    if (!stream->sos) {
+        return APR_EGENERAL;
     }
-    
-    if (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(stream->bbout)) {
-        status = h2_transfer_brigade(bb, stream->bbout, stream->pool, 
-                                     plen, peos);
-    }
-    else {
-        *plen = 0;
-        *peos = 0;
-    }
-
-    if (trailers && stream->response) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                      "h2_stream(%ld-%d): read_to, saving trailers",
-                      stream->session->id, stream->id);
-        h2_response_set_trailers(stream->response, trailers);
-    }
-    
-    if (status == APR_SUCCESS && !*peos && !*plen) {
-        status = APR_EAGAIN;
-    }
-    H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream read_to_post");
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
-                  stream->session->id, stream->id, (long)*plen, *peos);
-    return status;
+    return stream->sos->read_to(stream->sos, bb, plen, peos);
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
-int h2_stream_is_suspended(h2_stream *stream)
-{
-    AP_DEBUG_ASSERT(stream);
-    return stream->suspended;
-}
-
-int h2_stream_input_is_open(h2_stream *stream) 
+int h2_stream_input_is_open(const h2_stream *stream) 
 {
     return input_open(stream);
 }
 
-int h2_stream_needs_submit(h2_stream *stream)
+int h2_stream_needs_submit(const h2_stream *stream)
 {
     switch (stream->state) {
         case H2_STREAM_ST_OPEN:
         case H2_STREAM_ST_CLOSED_INPUT:
         case H2_STREAM_ST_CLOSED_OUTPUT:
         case H2_STREAM_ST_CLOSED:
