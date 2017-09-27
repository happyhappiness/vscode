                           APLOGNO(02938) "h2_stream(%ld-%d): reading data",
                           session->id, (int)stream_id);
             return NGHTTP2_ERR_CALLBACK_FAILURE;
     }
     
     if (eos) {
+        apr_table_t *trailers = h2_stream_get_trailers(stream);
+        if (trailers && !apr_is_empty_table(trailers)) {
+            h2_ngheader *nh;
+            int rv;
+            
+            nh = h2_util_ngheader_make(stream->pool, trailers);
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                          "h2_stream(%ld-%d): submit %d trailers",
+                          session->id, (int)stream_id,(int) nh->nvlen);
+            rv = nghttp2_submit_trailer(ng2s, stream->id, nh->nv, nh->nvlen);
+            if (rv < 0) {
+                nread = rv;
+            }
+            *data_flags |= NGHTTP2_DATA_FLAG_NO_END_STREAM;
+        }
+        
         *data_flags |= NGHTTP2_DATA_FLAG_EOF;
     }
     
     return (ssize_t)nread;
 }
 
 typedef struct {
     nghttp2_nv *nv;
     size_t nvlen;
     size_t offset;
 } nvctx_t;
 
-static int submit_response(h2_session *session, h2_response *response)
-{
-    nghttp2_data_provider provider;
-    int rv;
-    
-    memset(&provider, 0, sizeof(provider));
-    provider.source.fd = response->stream_id;
-    provider.read_callback = stream_data_cb;
-    
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
-                  "h2_stream(%ld-%d): submitting response %s",
-                  session->id, response->stream_id, response->status);
-    
-    rv = nghttp2_submit_response(session->ngh2, response->stream_id,
-                                 response->ngheader->nv, 
-                                 response->ngheader->nvlen, &provider);
-    
-    if (rv != 0) {
-        ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
-                      APLOGNO(02939) "h2_stream(%ld-%d): submit_response: %s",
-                      session->id, response->stream_id, nghttp2_strerror(rv));
-    }
-    else {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
-                      "h2_stream(%ld-%d): submitted response %s, rv=%d",
-                      session->id, response->stream_id, 
-                      response->status, rv);
-    }
-    return rv;
-}
-
-/* Start submitting the response to a stream request. This is possible
+/**
+ * Start submitting the response to a stream request. This is possible
  * once we have all the response headers. The response body will be
  * read by the session using the callback we supply.
  */
-apr_status_t h2_session_handle_response(h2_session *session, h2_stream *stream)
+static apr_status_t submit_response(h2_session *session, h2_stream *stream)
 {
     apr_status_t status = APR_SUCCESS;
     int rv = 0;
     AP_DEBUG_ASSERT(session);
     AP_DEBUG_ASSERT(stream);
-    AP_DEBUG_ASSERT(stream->response);
+    AP_DEBUG_ASSERT(stream->response || stream->rst_error);
     
-    if (stream->response->ngheader) {
-        rv = submit_response(session, stream->response);
+    if (stream->submitted) {
+        rv = NGHTTP2_PROTOCOL_ERROR;
+    }
+    else if (stream->response && stream->response->headers) {
+        nghttp2_data_provider provider;
+        h2_response *response = stream->response;
+        h2_ngheader *ngh;
+        const h2_priority *prio;
+        
+        memset(&provider, 0, sizeof(provider));
+        provider.source.fd = stream->id;
+        provider.read_callback = stream_data_cb;
+        
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                      "h2_stream(%ld-%d): submit response %d",
+                      session->id, stream->id, response->http_status);
+        
+        /* If this stream is not a pushed one itself,
+         * and HTTP/2 server push is enabled here,
+         * and the response is in the range 200-299 *),
+         * and the remote side has pushing enabled,
+         * -> find and perform any pushes on this stream
+         *    *before* we submit the stream response itself.
+         *    This helps clients avoid opening new streams on Link
+         *    headers that get pushed right afterwards.
+         * 
+         * *) the response code is relevant, as we do not want to 
+         *    make pushes on 401 or 403 codes, neiterh on 301/302
+         *    and friends. And if we see a 304, we do not push either
+         *    as the client, having this resource in its cache, might
+         *    also have the pushed ones as well.
+         */
+        if (!stream->initiated_on
+            && h2_config_geti(session->config, H2_CONF_PUSH)
+            && H2_HTTP_2XX(response->http_status)
+            && h2_session_push_enabled(session)) {
+            
+            h2_stream_submit_pushes(stream);
+        }
+        
+        prio = h2_stream_get_priority(stream);
+        if (prio) {
+            h2_session_set_prio(session, stream, prio);
+            /* no showstopper if that fails for some reason */
+        }
+        
+        ngh = h2_util_ngheader_make_res(stream->pool, response->http_status, 
+                                        response->headers);
+        rv = nghttp2_submit_response(session->ngh2, response->stream_id,
+                                     ngh->nv, ngh->nvlen, &provider);
+        
     }
     else {
+        int err = H2_STREAM_RST(stream, H2_ERR_PROTOCOL_ERROR);
+        
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                      "h2_stream(%ld-%d): RST_STREAM, err=%d",
+                      session->id, stream->id, err);
+
         rv = nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
-                                       stream->id, NGHTTP2_PROTOCOL_ERROR);
+                                       stream->id, err);
     }
     
+    stream->submitted = 1;
+
     if (nghttp2_is_fatal(rv)) {
         status = APR_EGENERAL;
         h2_session_abort_int(session, rv);
         ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                       APLOGNO(02940) "submit_response: %s", 
                       nghttp2_strerror(rv));
     }
+    
     return status;
 }
 
-int h2_session_is_done(h2_session *session)
+struct h2_stream *h2_session_push(h2_session *session, h2_stream *is,
+                                  h2_push *push)
 {
-    AP_DEBUG_ASSERT(session);
-    return (session->aborted
-            || !session->ngh2
-            || (!nghttp2_session_want_read(session->ngh2)
-                && !nghttp2_session_want_write(session->ngh2)));
+    apr_status_t status;
+    h2_stream *stream;
+    h2_ngheader *ngh;
+    int nid;
+    
+    ngh = h2_util_ngheader_make_req(is->pool, push->req);
+    nid = nghttp2_submit_push_promise(session->ngh2, 0, is->id, 
+                                      ngh->nv, ngh->nvlen, NULL);
+                                      
+    if (nid <= 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                      "h2_stream(%ld-%d): submitting push promise fail: %s",
+                      session->id, is->id, nghttp2_strerror(nid));
+        return NULL;
+    }
+
+    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                  "h2_stream(%ld-%d): promised new stream %d for %s %s on %d",
+                  session->id, is->id, nid,
+                  push->req->method, push->req->path, is->id);
+                  
+    stream = h2_session_open_stream(session, nid);
+    if (stream) {
+        h2_stream_set_h2_request(stream, is->id, push->req);
+        status = stream_schedule(session, stream, 1);
+        if (status != APR_SUCCESS) {
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
+                          "h2_stream(%ld-%d): scheduling push stream",
+                          session->id, stream->id);
+            h2_stream_cleanup(stream);
+            stream = NULL;
+        }
+        ++session->unsent_promises;
+    }
+    else {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                      "h2_stream(%ld-%d): failed to create stream obj %d",
+                      session->id, is->id, nid);
+    }
+
+    if (!stream) {
+        /* try to tell the client that it should not wait. */
+        nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE, nid,
+                                  NGHTTP2_INTERNAL_ERROR);
+    }
+    
+    return stream;
 }
 
-static int log_stream(void *ctx, h2_stream *stream)
+static int valid_weight(float f) 
 {
-    h2_session *session = (h2_session *)ctx;
-    AP_DEBUG_ASSERT(session);
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
-                  "h2_stream(%ld-%d): in set, suspended=%d, aborted=%d, "
-                  "has_data=%d",
-                  session->id, stream->id, stream->suspended, stream->aborted,
-                  h2_mplx_out_has_data_for(session->mplx, stream->id));
-    return 1;
+    int w = (int)f;
+    return (w < NGHTTP2_MIN_WEIGHT? NGHTTP2_MIN_WEIGHT : 
+            (w > NGHTTP2_MAX_WEIGHT)? NGHTTP2_MAX_WEIGHT : w);
 }
 
-void h2_session_log_stats(h2_session *session)
+apr_status_t h2_session_set_prio(h2_session *session, h2_stream *stream, 
+                                 const h2_priority *prio)
 {
-    AP_DEBUG_ASSERT(session);
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
-                  "h2_session(%ld): %d open streams",
-                  session->id, (int)h2_stream_set_size(session->streams));
-    h2_stream_set_iter(session->streams, log_stream, session);
+    apr_status_t status = APR_SUCCESS;
+#ifdef H2_NG2_CHANGE_PRIO
+    nghttp2_stream *s_grandpa, *s_parent, *s;
+    
+    s = nghttp2_session_find_stream(session->ngh2, stream->id);
+    if (!s) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                      "h2_stream(%ld-%d): lookup of nghttp2_stream failed",
+                      session->id, stream->id);
+        return APR_EINVAL;
+    }
+    
+    s_parent = nghttp2_stream_get_parent(s);
+    if (s_parent) {
+        nghttp2_priority_spec ps;
+        int id_parent, id_grandpa, w_parent, w, rv = 0;
+        char *ptype = "AFTER";
+        h2_dependency dep = prio->dependency;
+        
+        id_parent = nghttp2_stream_get_stream_id(s_parent);
+        s_grandpa = nghttp2_stream_get_parent(s_parent);
+        if (s_grandpa) {
+            id_grandpa = nghttp2_stream_get_stream_id(s_grandpa);
+        }
+        else {
+            /* parent of parent does not exist, 
+             * only possible if parent == root */
+            dep = H2_DEPENDANT_AFTER;
+        }
+        
+        switch (dep) {
+            case H2_DEPENDANT_INTERLEAVED:
+                /* PUSHed stream is to be interleaved with initiating stream.
+                 * It is made a sibling of the initiating stream and gets a
+                 * proportional weight [1, MAX_WEIGHT] of the initiaing
+                 * stream weight.
+                 */
+                ptype = "INTERLEAVED";
+                w_parent = nghttp2_stream_get_weight(s_parent);
+                w = valid_weight(w_parent * ((float)prio->weight / NGHTTP2_MAX_WEIGHT));
+                nghttp2_priority_spec_init(&ps, id_grandpa, w, 0);
+                break;
+                
+            case H2_DEPENDANT_BEFORE:
+                /* PUSHed stream os to be sent BEFORE the initiating stream.
+                 * It gets the same weight as the initiating stream, replaces
+                 * that stream in the dependency tree and has the initiating
+                 * stream as child.
+                 */
+                ptype = "BEFORE";
+                w = w_parent = nghttp2_stream_get_weight(s_parent);
+                nghttp2_priority_spec_init(&ps, stream->id, w_parent, 0);
+                id_grandpa = nghttp2_stream_get_stream_id(s_grandpa);
+                rv = nghttp2_session_change_stream_priority(session->ngh2, id_parent, &ps);
+                if (rv < 0) {
+                    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                                  "h2_stream(%ld-%d): PUSH BEFORE2, weight=%d, "
+                                  "depends=%d, returned=%d",
+                                  session->id, id_parent, ps.weight, ps.stream_id, rv);
+                    return APR_EGENERAL;
+                }
+                nghttp2_priority_spec_init(&ps, id_grandpa, w, 0);
+                break;
+                
+            case H2_DEPENDANT_AFTER:
+                /* The PUSHed stream is to be sent after the initiating stream.
+                 * Give if the specified weight and let it depend on the intiating
+                 * stream.
+                 */
+                /* fall through, it's the default */
+            default:
+                nghttp2_priority_spec_init(&ps, id_parent, valid_weight(prio->weight), 0);
+                break;
+        }
+
+
+        rv = nghttp2_session_change_stream_priority(session->ngh2, stream->id, &ps);
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+                      "h2_stream(%ld-%d): PUSH %s, weight=%d, "
+                      "depends=%d, returned=%d",
+                      session->id, stream->id, ptype, 
+                      ps.weight, ps.stream_id, rv);
+        status = (rv < 0)? APR_EGENERAL : APR_SUCCESS;
+    }
+#else
+    (void)session;
+    (void)stream;
+    (void)prio;
+    (void)valid_weight;
+#endif
+    return status;
+}
+
+apr_status_t h2_session_stream_destroy(h2_session *session, h2_stream *stream)
+{
+    apr_pool_t *pool = h2_stream_detach_pool(stream);
+
+    /* this may be called while the session has already freed
+     * some internal structures. */
+    if (session->mplx) {
+        h2_mplx_stream_done(session->mplx, stream->id, stream->rst_error);
+        if (session->last_stream == stream) {
+            session->last_stream = NULL;
+        }
+    }
+    
+    if (session->streams) {
+        h2_stream_set_remove(session->streams, stream->id);
+    }
+    h2_stream_destroy(stream);
+    
+    if (pool) {
+        apr_pool_clear(pool);
+        if (session->spare) {
+            apr_pool_destroy(session->spare);
+        }
+        session->spare = pool;
+    }
+    return APR_SUCCESS;
 }
 
 static int frame_print(const nghttp2_frame *frame, char *buffer, size_t maxlen)
 {
     char scratch[128];
     size_t s_len = sizeof(scratch)/sizeof(scratch[0]);
