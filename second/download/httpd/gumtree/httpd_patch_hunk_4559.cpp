     apr_off_t len = 0;
     int eos = 0;
     h2_headers *headers;
     
     ap_assert(stream);
     ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
-                  "h2_stream(%ld-%d): on_resume", session->id, stream->id);
-        
+                  H2_STRM_MSG(stream, "on_resume"));
+    
 send_headers:
     headers = NULL;
     status = h2_stream_out_prepare(stream, &len, &eos, &headers);
     ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
-                  "h2_stream(%ld-%d): prepared len=%ld, eos=%d", 
-                  session->id, stream->id, (long)len, eos);
+                  H2_STRM_MSG(stream, "prepared len=%ld, eos=%d"), 
+                  (long)len, eos);
     if (headers) {
         status = on_stream_headers(session, stream, headers, len, eos);
         if (status != APR_SUCCESS || stream->rst_error) {
             return status;
         }
         goto send_headers;
     }
     else if (status != APR_EAGAIN) {
+        /* we have DATA to send */
         if (!stream->has_response) {
-            int err = H2_STREAM_RST(stream, H2_ERR_PROTOCOL_ERROR);
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03466)
-                          "h2_stream(%ld-%d): no response, RST_STREAM, err=%d",
-                          session->id, stream->id, err);
-            nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
-                                      stream->id, err);
+            /* but no response */
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
+                          H2_STRM_LOG(APLOGNO(03466), stream, 
+                          "no response, RST_STREAM"));
+            h2_stream_rst(stream, H2_ERR_PROTOCOL_ERROR);
             return APR_SUCCESS;
         } 
         rv = nghttp2_session_resume_data(session->ngh2, stream->id);
         session->have_written = 1;
         ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
-                      APLOG_ERR : APLOG_DEBUG, 0, session->c,
-                      APLOGNO(02936) 
-                      "h2_stream(%ld-%d): resuming %s",
-                      session->id, stream->id, rv? nghttp2_strerror(rv) : "");
+                      APLOG_ERR : APLOG_DEBUG, 0, session->c,  
+                      H2_STRM_LOG(APLOGNO(02936), stream, "resumed"));
     }
     return status;
 }
 
-static apr_status_t h2_session_receive(void *ctx, const char *data, 
-                                       apr_size_t len, apr_size_t *readlen)
+static void h2_session_in_flush(h2_session *session)
 {
-    h2_session *session = ctx;
-    ssize_t n;
+    int id;
     
-    if (len > 0) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
-                      "h2_session(%ld): feeding %ld bytes to nghttp2",
-                      session->id, (long)len);
-        n = nghttp2_session_mem_recv(session->ngh2, (const uint8_t *)data, len);
-        if (n < 0) {
-            if (nghttp2_is_fatal((int)n)) {
-                dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, (int)n, nghttp2_strerror((int)n));
-                return APR_EGENERAL;
+    while ((id = h2_iq_shift(session->in_process)) > 0) {
+        h2_stream *stream = h2_session_stream_get(session, id);
+        if (stream) {
+            ap_assert(!stream->scheduled);
+            if (h2_stream_prep_processing(stream) == APR_SUCCESS) {
+                h2_mplx_process(session->mplx, stream, stream_pri_cmp, session);
+            }
+            else {
+                h2_stream_rst(stream, H2_ERR_INTERNAL_ERROR);
             }
         }
-        else {
-            *readlen = n;
-            session->io.bytes_read += n;
+    }
+
+    while ((id = h2_iq_shift(session->in_pending)) > 0) {
+        h2_stream *stream = h2_session_stream_get(session, id);
+        if (stream) {
+            h2_stream_flush_input(stream);
         }
     }
-    return APR_SUCCESS;
 }
 
-static apr_status_t h2_session_read(h2_session *session, int block)
+static apr_status_t session_read(h2_session *session, apr_size_t readlen, int block)
 {
     apr_status_t status, rstatus = APR_EAGAIN;
     conn_rec *c = session->c;
     apr_off_t read_start = session->io.bytes_read;
     
     while (1) {
         /* H2_IN filter handles all incoming data against the session.
          * We just pull at the filter chain to make it happen */
         status = ap_get_brigade(c->input_filters,
                                 session->bbtmp, AP_MODE_READBYTES,
                                 block? APR_BLOCK_READ : APR_NONBLOCK_READ,
-                                APR_BUCKET_BUFF_SIZE);
+                                H2MAX(APR_BUCKET_BUFF_SIZE, readlen));
         /* get rid of any possible data we do not expect to get */
         apr_brigade_cleanup(session->bbtmp); 
 
         switch (status) {
             case APR_SUCCESS:
                 /* successful read, reset our idle timers */
