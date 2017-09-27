         h2_stream_set_iter(session->streams, resume_on_data, &ctx);
         return ctx.resume_count;
     }
     return 0;
 }
 
-static void update_window(void *ctx, int stream_id, apr_size_t bytes_read)
-{
-    h2_session *session = (h2_session*)ctx;
-    nghttp2_session_consume(session->ngh2, stream_id, bytes_read);
-}
-
-static apr_status_t h2_session_update_windows(h2_session *session)
-{
-    return h2_mplx_in_update_windows(session->mplx, update_window, session);
-}
-
-apr_status_t h2_session_write(h2_session *session, apr_interval_time_t timeout)
-{
-    apr_status_t status = APR_EAGAIN;
-    h2_stream *stream = NULL;
-    int flush_output = 0;
-    
-    AP_DEBUG_ASSERT(session);
-    
-    /* Check that any pending window updates are sent. */
-    status = h2_session_update_windows(session);
-    if (status == APR_SUCCESS) {
-        flush_output = 1;
-    }
-    else if (status != APR_EAGAIN) {
-        return status;
-    }
-    
-    if (h2_session_want_write(session)) {
-        int rv;
-        status = APR_SUCCESS;
-        rv = nghttp2_session_send(session->ngh2);
-        if (rv != 0) {
-            ap_log_cerror( APLOG_MARK, APLOG_DEBUG, 0, session->c,
-                          "h2_session: send: %s", nghttp2_strerror(rv));
-            if (nghttp2_is_fatal(rv)) {
-                h2_session_abort_int(session, rv);
-                status = APR_ECONNABORTED;
-            }
-        }
-        flush_output = 1;
-    }
-    
-    /* If we have responses ready, submit them now. */
-    while ((stream = h2_mplx_next_submit(session->mplx, 
-                                         session->streams)) != NULL) {
-        status = h2_session_handle_response(session, stream);
-        flush_output = 1;
-    }
-    
-    if (h2_session_resume_streams_with_data(session) > 0) {
-        flush_output = 1;
-    }
-    
-    if (!flush_output && timeout > 0 && !h2_session_want_write(session)) {
-        status = h2_mplx_out_trywait(session->mplx, timeout, session->iowait);
-
-        if (status != APR_TIMEUP
-            && h2_session_resume_streams_with_data(session) > 0) {
-            flush_output = 1;
-        }
-        else {
-            /* nothing happened to ongoing streams, do some house-keeping */
-        }
-    }
-    
-    if (h2_session_want_write(session)) {
-        int rv;
-        status = APR_SUCCESS;
-        rv = nghttp2_session_send(session->ngh2);
-        if (rv != 0) {
-            ap_log_cerror( APLOG_MARK, APLOG_DEBUG, 0, session->c,
-                          "h2_session: send2: %s", nghttp2_strerror(rv));
-            if (nghttp2_is_fatal(rv)) {
-                h2_session_abort_int(session, rv);
-                status = APR_ECONNABORTED;
-            }
-        }
-        flush_output = 1;
-    }
-    
-    if (flush_output) {
-        h2_conn_io_flush(&session->io);
-    }
-    
-    return status;
-}
-
 h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
 {
-    AP_DEBUG_ASSERT(session);
-    return h2_stream_set_get(session->streams, stream_id);
+    if (!session->last_stream || stream_id != session->last_stream->id) {
+        session->last_stream = h2_stream_set_get(session->streams, stream_id);
+    }
+    return session->last_stream;
 }
 
 /* h2_io_on_read_cb implementation that offers the data read
  * directly to the session for consumption.
  */
 static apr_status_t session_receive(const char *data, apr_size_t len,
