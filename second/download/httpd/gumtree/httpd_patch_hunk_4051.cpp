 
 void h2_stream_rst(h2_stream *stream, int error_code)
 {
     stream->rst_error = error_code;
     close_input(stream);
     close_output(stream);
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                   "h2_stream(%ld-%d): reset, error=%d", 
                   stream->session->id, stream->id, error_code);
 }
 
+struct h2_response *h2_stream_get_response(h2_stream *stream)
+{
+    return stream->sos? stream->sos->response : NULL;
+}
+
 apr_status_t h2_stream_set_response(h2_stream *stream, h2_response *response,
                                     apr_bucket_brigade *bb)
 {
     apr_status_t status = APR_SUCCESS;
+    h2_sos *sos;
+    
     if (!output_open(stream)) {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, stream->session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                       "h2_stream(%ld-%d): output closed", 
                       stream->session->id, stream->id);
         return APR_ECONNRESET;
     }
     
-    stream->response = response;
-    if (bb && !APR_BRIGADE_EMPTY(bb)) {
-        int move_all = INT_MAX;
-        /* we can move file handles from h2_mplx into this h2_stream as many
-         * as we want, since the lifetimes are the same and we are not freeing
-         * the ones in h2_mplx->io before this stream is done. */
-        H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream set_response_pre");
-        status = h2_util_move(stream->bbout, bb, 16 * 1024, &move_all,  
-                              "h2_stream_set_response");
-        H2_STREAM_OUT(APLOG_TRACE2, stream, "h2_stream set_response_post");
+    sos = h2_sos_mplx_create(stream, response);
+    if (sos->response->sos_filter) {
+        sos = h2_filter_sos_create(sos->response->sos_filter, sos); 
     }
+    stream->sos = sos;
     
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, stream->session->c,
+    status = stream->sos->buffer(stream->sos, bb);
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                   "h2_stream(%ld-%d): set_response(%d)", 
-                  stream->session->id, stream->id, response->http_status);
+                  stream->session->id, stream->id, stream->sos->response->http_status);
     return status;
 }
 
 apr_status_t h2_stream_set_request(h2_stream *stream, request_rec *r)
 {
     apr_status_t status;
     AP_DEBUG_ASSERT(stream);
     if (stream->rst_error) {
         return APR_ECONNRESET;
     }
     set_state(stream, H2_STREAM_ST_OPEN);
     status = h2_request_rwrite(stream->request, r);
+    stream->request->serialize = h2_config_geti(h2_config_rget(r), 
+                                                H2_CONF_SER_HEADERS);
+
     return status;
 }
 
 void h2_stream_set_h2_request(h2_stream *stream, int initiated_on,
                               const h2_request *req)
 {
     h2_request_copy(stream->pool, stream->request, req);
-    stream->initiated_on = initiated_on;
+    stream->request->initiated_on = initiated_on;
     stream->request->eoh = 0;
 }
 
 apr_status_t h2_stream_add_header(h2_stream *stream,
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
