                                  const h2_priority *prio)
 {
     apr_status_t status = APR_SUCCESS;
 #ifdef H2_NG2_CHANGE_PRIO
     nghttp2_stream *s_grandpa, *s_parent, *s;
     
+    if (prio == NULL) {
+        /* we treat this as a NOP */
+        return APR_SUCCESS;
+    }
     s = nghttp2_session_find_stream(session->ngh2, stream->id);
     if (!s) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                       "h2_stream(%ld-%d): lookup of nghttp2_stream failed",
                       session->id, stream->id);
         return APR_EINVAL;
     }
     
     s_parent = nghttp2_stream_get_parent(s);
     if (s_parent) {
         nghttp2_priority_spec ps;
-        int id_parent, id_grandpa, w_parent, w, rv = 0;
-        char *ptype = "AFTER";
+        int id_parent, id_grandpa, w_parent, w;
+        int rv = 0;
+        const char *ptype = "AFTER";
         h2_dependency dep = prio->dependency;
         
         id_parent = nghttp2_stream_get_stream_id(s_parent);
         s_grandpa = nghttp2_stream_get_parent(s_parent);
         if (s_grandpa) {
             id_grandpa = nghttp2_stream_get_stream_id(s_grandpa);
