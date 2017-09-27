 }
 
 apr_status_t h2_stream_add_header(h2_stream *stream,
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
 {
+    h2_session *session = stream->session;
     int error = 0;
-    ap_assert(stream);
+    apr_status_t status;
     
     if (stream->has_response) {
         return APR_EINVAL;    
     }
     ++stream->request_headers_added;
     if (name[0] == ':') {
-        if ((vlen) > stream->session->s->limit_req_line) {
+        if ((vlen) > session->s->limit_req_line) {
             /* pseudo header: approximation of request line size check */
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                          "h2_stream(%ld-%d): pseudo header %s too long", 
-                          stream->session->id, stream->id, name);
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
+                          H2_STRM_MSG(stream, "pseudo %s too long"), name);
             error = HTTP_REQUEST_URI_TOO_LARGE;
         }
     }
-    else if ((nlen + 2 + vlen) > stream->session->s->limit_req_fieldsize) {
+    else if ((nlen + 2 + vlen) > session->s->limit_req_fieldsize) {
         /* header too long */
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                      "h2_stream(%ld-%d): header %s too long", 
-                      stream->session->id, stream->id, name);
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
+                      H2_STRM_MSG(stream, "header %s too long"), name);
         error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
     }
     
-    if (stream->request_headers_added 
-        > stream->session->s->limit_req_fields + 4) {
+    if (stream->request_headers_added > session->s->limit_req_fields + 4) {
         /* too many header lines, include 4 pseudo headers */
         if (stream->request_headers_added 
-            > stream->session->s->limit_req_fields + 4 + 100) {
+            > session->s->limit_req_fields + 4 + 100) {
             /* yeah, right */
+            h2_stream_rst(stream, H2_ERR_ENHANCE_YOUR_CALM);
             return APR_ECONNRESET;
         }
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                      "h2_stream(%ld-%d): too many header lines", 
-                      stream->session->id, stream->id);
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
+                      H2_STRM_MSG(stream, "too many header lines")); 
         error = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE;
     }
     
-    if (h2_stream_is_scheduled(stream)) {
-        return add_trailer(stream, name, nlen, value, vlen);
-    }
-    else if (error) {
-        return h2_stream_set_error(stream, error); 
+    if (error) {
+        set_error_response(stream, error);
+        return APR_EINVAL; 
     }
-    else {
+    else if (H2_SS_IDLE == stream->state) {
         if (!stream->rtmp) {
             stream->rtmp = h2_req_create(stream->id, stream->pool, 
                                          NULL, NULL, NULL, NULL, NULL, 0);
         }
-        if (stream->state != H2_STREAM_ST_OPEN) {
-            return APR_ECONNRESET;
-        }
-        return h2_request_add_header(stream->rtmp, stream->pool,
-                                     name, nlen, value, vlen);
+        status = h2_request_add_header(stream->rtmp, stream->pool,
+                                       name, nlen, value, vlen);
     }
-}
-
-apr_status_t h2_stream_schedule(h2_stream *stream, int eos, int push_enabled, 
-                                h2_stream_pri_cmp *cmp, void *ctx)
-{
-    apr_status_t status = APR_EINVAL;
-    ap_assert(stream);
-    ap_assert(stream->session);
-    ap_assert(stream->session->mplx);
-    
-    if (!stream->scheduled) {
-        if (eos) {
-            close_input(stream);
-        }
-
-        if (h2_stream_is_ready(stream)) {
-            /* already have a resonse, probably a HTTP error code */
-            return h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
-        }
-        else if (!stream->request && stream->rtmp) {
-            /* This is the common case: a h2_request was being assembled, now
-             * it gets finalized and checked for completness */
-            status = h2_request_end_headers(stream->rtmp, stream->pool, eos);
-            if (status == APR_SUCCESS) {
-                stream->rtmp->serialize = h2_config_geti(stream->session->config,
-                                                         H2_CONF_SER_HEADERS); 
-
-                stream->request = stream->rtmp;
-                stream->rtmp = NULL;
-                stream->scheduled = 1;
-                
-                stream->push_policy = h2_push_policy_determine(stream->request->headers, 
-                                                               stream->pool, push_enabled);
-            
-                
-                status = h2_mplx_process(stream->session->mplx, stream, cmp, ctx);
-                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                              "h2_stream(%ld-%d): scheduled %s %s://%s%s "
-                              "chunked=%d",
-                              stream->session->id, stream->id,
-                              stream->request->method, stream->request->scheme,
-                              stream->request->authority, stream->request->path,
-                              stream->request->chunked);
-                return status;
-            }
-        }
-        else {
-            status = APR_ECONNRESET;
-        }
-    }
-    
-    h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
-                  "h2_stream(%ld-%d): RST=2 (internal err) %s %s://%s%s",
-                  stream->session->id, stream->id,
-                  stream->request->method, stream->request->scheme,
-                  stream->request->authority, stream->request->path);
-    return status;
-}
-
-int h2_stream_is_scheduled(const h2_stream *stream)
-{
-    return stream->scheduled;
-}
-
-apr_status_t h2_stream_close_input(h2_stream *stream)
-{
-    conn_rec *c = stream->session->c;
-    apr_status_t status;
-    apr_bucket_brigade *tmp;
-    apr_bucket *b;
-
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
-                  "h2_stream(%ld-%d): closing input",
-                  stream->session->id, stream->id);
-    if (stream->rst_error) {
-        return APR_ECONNRESET;
+    else  {
+        status = add_trailer(stream, name, nlen, value, vlen);
     }
-    
-    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
-    if (stream->trailers && !apr_is_empty_table(stream->trailers)) {
-        h2_headers *r = h2_headers_create(HTTP_OK, stream->trailers, 
-                                          NULL, stream->pool);
-        b = h2_bucket_headers_create(c->bucket_alloc, r);
-        APR_BRIGADE_INSERT_TAIL(tmp, b);
-        stream->trailers = NULL;
+    if (status != APR_SUCCESS) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
+                      H2_STRM_MSG(stream, "header %s not accepted"), name);
+        h2_stream_dispatch(stream, H2_SEV_CANCELLED);
     }
-    
-    b = apr_bucket_eos_create(c->bucket_alloc);
-    APR_BRIGADE_INSERT_TAIL(tmp, b);
-    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
-    apr_brigade_destroy(tmp);
     return status;
 }
 
-apr_status_t h2_stream_write_data(h2_stream *stream,
-                                  const char *data, size_t len, int eos)
-{
-    conn_rec *c = stream->session->c;
-    apr_status_t status = APR_SUCCESS;
-    apr_bucket_brigade *tmp;
-    
-    ap_assert(stream);
-    if (!stream->input) {
-        return APR_EOF;
-    }
-    if (input_closed(stream) || !stream->request) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
-                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
-                      stream->session->id, stream->id, input_closed(stream),
-                      stream->request != NULL);
-        return APR_EINVAL;
-    }
-
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
-                  "h2_stream(%ld-%d): add %ld input bytes", 
-                  stream->session->id, stream->id, (long)len);
-    
-    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
-    apr_brigade_write(tmp, NULL, NULL, data, len);
-    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
-    apr_brigade_destroy(tmp);
-    
-    stream->in_data_frames++;
-    stream->in_data_octets += len;
-    
-    if (eos) {
-        return h2_stream_close_input(stream);
-    }
-    
-    return status;
-}
-
-static apr_status_t fill_buffer(h2_stream *stream, apr_size_t amount)
+static apr_bucket *get_first_headers_bucket(apr_bucket_brigade *bb)
 {
-    conn_rec *c = stream->session->c;
-    apr_bucket *b;
-    apr_status_t status;
-    
-    if (!stream->output) {
-        return APR_EOF;
-    }
-    status = h2_beam_receive(stream->output, stream->out_buffer, 
-                             APR_NONBLOCK_READ, amount);
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c,
-                  "h2_stream(%ld-%d): beam_received",
-                  stream->session->id, stream->id);
-    /* The buckets we reveive are using the stream->out_buffer pool as
-     * lifetime which is exactly what we want since this is stream->pool.
-     *
-     * However: when we send these buckets down the core output filters, the
-     * filter might decide to setaside them into a pool of its own. And it
-     * might decide, after having sent the buckets, to clear its pool.
-     *
-     * This is problematic for file buckets because it then closed the contained
-     * file. Any split off buckets we sent afterwards will result in a 
-     * APR_EBADF.
-     */
-    for (b = APR_BRIGADE_FIRST(stream->out_buffer);
-         b != APR_BRIGADE_SENTINEL(stream->out_buffer);
-         b = APR_BUCKET_NEXT(b)) {
-        if (APR_BUCKET_IS_FILE(b)) {
-            apr_bucket_file *f = (apr_bucket_file *)b->data;
-            apr_pool_t *fpool = apr_file_pool_get(f->fd);
-            if (fpool != c->pool) {
-                apr_bucket_setaside(b, c->pool);
-                if (!stream->files) {
-                    stream->files = apr_array_make(stream->pool, 
-                                                   5, sizeof(apr_file_t*));
-                }
-                APR_ARRAY_PUSH(stream->files, apr_file_t*) = f->fd;
+    if (bb) {
+        apr_bucket *b = APR_BRIGADE_FIRST(bb);
+        while (b != APR_BRIGADE_SENTINEL(bb)) {
+            if (H2_BUCKET_IS_HEADERS(b)) {
+                return b;
             }
+            b = APR_BUCKET_NEXT(b);
         }
     }
-    return status;
+    return NULL;
 }
 
-apr_status_t h2_stream_set_error(h2_stream *stream, int http_status)
+static apr_status_t add_data(h2_stream *stream, apr_off_t requested,
+                             apr_off_t *plen, int *peos, int *complete, 
+                             h2_headers **pheaders)
 {
-    h2_headers *response;
+    apr_bucket *b, *e;
     
-    if (h2_stream_is_ready(stream)) {
-        return APR_EINVAL;
+    *peos = 0;
+    *plen = 0;
+    *complete = 0;
+    if (pheaders) {
+        *pheaders = NULL;
     }
-    if (stream->rtmp) {
-        stream->request = stream->rtmp;
-        stream->rtmp = NULL;
-    }
-    response = h2_headers_die(http_status, stream->request, stream->pool);
-    prepend_response(stream, response);
-    h2_beam_close(stream->output);
-    return APR_SUCCESS;
-}
 
-static apr_bucket *get_first_headers_bucket(apr_bucket_brigade *bb)
-{
-    if (bb) {
-        apr_bucket *b = APR_BRIGADE_FIRST(bb);
-        while (b != APR_BRIGADE_SENTINEL(bb)) {
-            if (H2_BUCKET_IS_HEADERS(b)) {
-                return b;
+    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "add_data");
+    b = APR_BRIGADE_FIRST(stream->out_buffer);
+    while (b != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
+        e = APR_BUCKET_NEXT(b);
+        if (APR_BUCKET_IS_METADATA(b)) {
+            if (APR_BUCKET_IS_FLUSH(b)) {
+                APR_BUCKET_REMOVE(b);
+                apr_bucket_destroy(b);
             }
-            b = APR_BUCKET_NEXT(b);
+            else if (APR_BUCKET_IS_EOS(b)) {
+                *peos = 1;
+                return APR_SUCCESS;
+            }
+            else if (H2_BUCKET_IS_HEADERS(b)) {
+                if (*plen > 0) {
+                    /* data before the response, can only return up to here */
+                    return APR_SUCCESS;
+                }
+                else if (pheaders) {
+                    *pheaders = h2_bucket_headers_get(b);
+                    APR_BUCKET_REMOVE(b);
+                    apr_bucket_destroy(b);
+                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
+                                  H2_STRM_MSG(stream, "prep, -> response %d"), 
+                                  (*pheaders)->status);
+                    return APR_SUCCESS;
+                }
+                else {
+                    return APR_EAGAIN;
+                }
+            }
+        }
+        else if (b->length == 0) {
+            APR_BUCKET_REMOVE(b);
+            apr_bucket_destroy(b);
         }
+        else {
+            ap_assert(b->length != (apr_size_t)-1);
+            *plen += b->length;
+            if (*plen >= requested) {
+                *plen = requested;
+                return APR_SUCCESS;
+            }
+        }
+        b = e;
     }
-    return NULL;
+    *complete = 1;
+    return APR_SUCCESS;
 }
 
 apr_status_t h2_stream_out_prepare(h2_stream *stream, apr_off_t *plen, 
-                                   int *peos, h2_headers **presponse)
+                                   int *peos, h2_headers **pheaders)
 {
-    conn_rec *c = stream->session->c;
     apr_status_t status = APR_SUCCESS;
-    apr_off_t requested;
-    apr_bucket *b, *e;
+    apr_off_t requested, missing, max_chunk = H2_DATA_CHUNK_SIZE;
+    conn_rec *c;
+    int complete;
 
-    if (presponse) {
-        *presponse = NULL;
-    }
+    ap_assert(stream);
     
     if (stream->rst_error) {
         *plen = 0;
         *peos = 1;
         return APR_ECONNRESET;
     }
     
-    if (!output_open(stream)) {
-        return APR_ECONNRESET;
-    }
+    c = stream->session->c;
     prep_output(stream);
 
-    if (*plen > 0) {
-        requested = H2MIN(*plen, H2_DATA_CHUNK_SIZE);
+    /* determine how much we'd like to send. We cannot send more than
+     * is requested. But we can reduce the size in case the master
+     * connection operates in smaller chunks. (TSL warmup) */
+    if (stream->session->io.write_size > 0) {
+        max_chunk = stream->session->io.write_size - 9; /* header bits */ 
     }
-    else {
-        requested = H2_DATA_CHUNK_SIZE;
+    requested = (*plen > 0)? H2MIN(*plen, max_chunk) : max_chunk;
+    
+    /* count the buffered data until eos or a headers bucket */
+    status = add_data(stream, requested, plen, peos, &complete, pheaders);
+    
+    if (status == APR_EAGAIN) {
+        /* TODO: ugly, someone needs to retrieve the response first */
+        h2_mplx_keep_active(stream->session->mplx, stream);
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                      H2_STRM_MSG(stream, "prep, response eagain"));
+        return status;
+    }
+    else if (status != APR_SUCCESS) {
+        return status;
     }
-    *plen = requested;
     
-    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_pre");
-    h2_util_bb_avail(stream->out_buffer, plen, peos);
-    if (!*peos && *plen < requested) {
-        /* try to get more data */
-        status = fill_buffer(stream, (requested - *plen) + H2_DATA_CHUNK_SIZE);
+    if (pheaders && *pheaders) {
+        return APR_SUCCESS;
+    }
+    
+    missing = H2MIN(requested, stream->max_mem) - *plen;
+    if (complete && !*peos && missing > 0) {
+        if (stream->output) {
+            H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "pre");
+            status = h2_beam_receive(stream->output, stream->out_buffer, 
+                                     APR_NONBLOCK_READ, 
+                                     stream->max_mem - *plen);
+            H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "post");
+        }
+        else {
+            status = APR_EOF;
+        }
+        
         if (APR_STATUS_IS_EOF(status)) {
             apr_bucket *eos = apr_bucket_eos_create(c->bucket_alloc);
             APR_BRIGADE_INSERT_TAIL(stream->out_buffer, eos);
+            *peos = 1;
             status = APR_SUCCESS;
         }
-        else if (status == APR_EAGAIN) {
-            /* did not receive more, it's ok */
-            status = APR_SUCCESS;
+        else if (status == APR_SUCCESS) {
+            /* do it again, now that we have gotten more */
+            status = add_data(stream, requested, plen, peos, &complete, pheaders);
         }
-        *plen = requested;
-        h2_util_bb_avail(stream->out_buffer, plen, peos);
     }
-    H2_STREAM_OUT_LOG(APLOG_TRACE2, stream, "h2_stream_out_prepare_post");
     
-    b = APR_BRIGADE_FIRST(stream->out_buffer);
-    while (b != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
-        e = APR_BUCKET_NEXT(b);
-        if (APR_BUCKET_IS_FLUSH(b)
-            || (!APR_BUCKET_IS_METADATA(b) && b->length == 0)) {
-            APR_BUCKET_REMOVE(b);
-            apr_bucket_destroy(b);
+    if (status == APR_SUCCESS) {
+        if (*peos || *plen) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                          H2_STRM_MSG(stream, "prepare, len=%ld eos=%d"),
+                          (long)*plen, *peos);
         }
         else {
-            break;
+            status = APR_EAGAIN;
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                          H2_STRM_MSG(stream, "prepare, no data"));
         }
-        b = e;
     }
-    
-    b = get_first_headers_bucket(stream->out_buffer);
-    if (b) {
-        /* there are HEADERS to submit */
-        *peos = 0;
-        *plen = 0;
-        if (b == APR_BRIGADE_FIRST(stream->out_buffer)) {
-            if (presponse) {
-                *presponse = h2_bucket_headers_get(b);
-                APR_BUCKET_REMOVE(b);
-                apr_bucket_destroy(b);
-                status = APR_SUCCESS;
-            }
-            else {
-                /* someone needs to retrieve the response first */
-                h2_mplx_keep_active(stream->session->mplx, stream->id);
-                status = APR_EAGAIN;
-            }
-        }
-        else {
-            apr_bucket *e = APR_BRIGADE_FIRST(stream->out_buffer);
-            while (e != APR_BRIGADE_SENTINEL(stream->out_buffer)) {
-                if (e == b) {
-                    break;
-                }
-                else if (e->length != (apr_size_t)-1) {
-                    *plen += e->length;
-                }
-                e = APR_BUCKET_NEXT(e);
-            }
-        }
-    }
-    
-    if (!*peos && !*plen && status == APR_SUCCESS 
-        && (!presponse || !*presponse)) {
-        status = APR_EAGAIN;
-    }
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, c,
-                  "h2_stream(%ld-%d): prepare, len=%ld eos=%d",
-                  c->id, stream->id, (long)*plen, *peos);
     return status;
 }
 
 static int is_not_headers(apr_bucket *b)
 {
     return !H2_BUCKET_IS_HEADERS(b);
