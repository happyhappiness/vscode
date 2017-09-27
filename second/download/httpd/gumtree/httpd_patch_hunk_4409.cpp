                           APLOGNO(02938) "h2_stream(%ld-%d): reading data",
                           session->id, (int)stream_id);
             return NGHTTP2_ERR_CALLBACK_FAILURE;
     }
     
     if (eos) {
-        apr_table_t *trailers = h2_stream_get_trailers(stream);
-        if (trailers && !apr_is_empty_table(trailers)) {
-            h2_ngheader *nh;
-            int rv;
-            
-            nh = h2_util_ngheader_make(stream->pool, trailers);
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03072)
-                          "h2_stream(%ld-%d): submit %d trailers",
-                          session->id, (int)stream_id,(int) nh->nvlen);
-            rv = nghttp2_submit_trailer(ng2s, stream->id, nh->nv, nh->nvlen);
-            if (rv < 0) {
-                nread = rv;
-            }
-            *data_flags |= NGHTTP2_DATA_FLAG_NO_END_STREAM;
-        }
-        
         *data_flags |= NGHTTP2_DATA_FLAG_EOF;
     }
-    
     return (ssize_t)nread;
 }
 
-typedef struct {
-    nghttp2_nv *nv;
-    size_t nvlen;
-    size_t offset;
-} nvctx_t;
-
 struct h2_stream *h2_session_push(h2_session *session, h2_stream *is,
                                   h2_push *push)
 {
     apr_status_t status;
     h2_stream *stream;
     h2_ngheader *ngh;
