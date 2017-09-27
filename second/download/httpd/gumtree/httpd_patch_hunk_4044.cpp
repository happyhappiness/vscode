     apr_status_t status = APR_SUCCESS;
 #ifdef H2_NG2_CHANGE_PRIO
     nghttp2_stream *s_grandpa, *s_parent, *s;
     
     s = nghttp2_session_find_stream(session->ngh2, stream->id);
     if (!s) {
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                       "h2_stream(%ld-%d): lookup of nghttp2_stream failed",
                       session->id, stream->id);
         return APR_EINVAL;
     }
     
     s_parent = nghttp2_stream_get_parent(s);
