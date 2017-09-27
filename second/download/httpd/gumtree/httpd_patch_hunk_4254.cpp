         }
     }
     
     return status;
 }
 
-typedef struct {
-    h2_session *session;
-    int resume_count;
-} resume_ctx;
-
-static int resume_on_data(void *ctx, void *val)
-{
-    h2_stream *stream = val;
-    resume_ctx *rctx = (resume_ctx*)ctx;
-    h2_session *session = rctx->session;
-    AP_DEBUG_ASSERT(session);
-    AP_DEBUG_ASSERT(stream);
-    
-    if (h2_stream_is_suspended(stream)) {
-        apr_status_t status;
-        apr_off_t len = -1;
-        int eos;
-        
-        status = h2_stream_out_prepare(stream, &len, &eos);
-        if (status == APR_SUCCESS) {
-            int rv;
-            h2_stream_set_suspended(stream, 0);
-            ++rctx->resume_count;
-            
-            rv = nghttp2_session_resume_data(session->ngh2, stream->id);
-            ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
-                          APLOG_ERR : APLOG_DEBUG, 0, session->c,
-                          APLOGNO(02936) 
-                          "h2_stream(%ld-%d): resuming %s, len=%ld, eos=%d",
-                          session->id, stream->id, 
-                          rv? nghttp2_strerror(rv) : "", (long)len, eos);
-        }
-    }
-    return 1;
-}
-
-static int h2_session_resume_streams_with_data(h2_session *session)
-{
-    AP_DEBUG_ASSERT(session);
-    if (!h2_ihash_is_empty(session->streams)
-        && session->mplx && !session->mplx->aborted) {
-        resume_ctx ctx;
-        
-        ctx.session      = session;
-        ctx.resume_count = 0;
-
-        /* Resume all streams where we have data in the out queue and
-         * which had been suspended before. */
-        h2_ihash_iter(session->streams, resume_on_data, &ctx);
-        return ctx.resume_count;
-    }
-    return 0;
-}
-
-h2_stream *h2_session_get_stream(h2_session *session, int stream_id)
-{
-    return h2_ihash_get(session->streams, stream_id);
-}
-
 static ssize_t stream_data_cb(nghttp2_session *ng2s,
                               int32_t stream_id,
                               uint8_t *buf,
                               size_t length,
                               uint32_t *data_flags,
                               nghttp2_data_source *source,
