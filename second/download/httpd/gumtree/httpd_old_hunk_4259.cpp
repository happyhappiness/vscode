    (void)prio;
    (void)valid_weight;
#endif
    return status;
}

apr_status_t h2_session_stream_destroy(h2_session *session, h2_stream *stream)
{
    apr_pool_t *pool = h2_stream_detach_pool(stream);

    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): cleanup by EOS bucket destroy", 
                  session->id, stream->id);
    /* this may be called while the session has already freed
     * some internal structures or even when the mplx is locked. */
    if (session->mplx) {
        h2_mplx_stream_done(session->mplx, stream->id, stream->rst_error);
    }
    
    if (session->streams) {
        h2_ihash_remove(session->streams, stream->id);
    }
    h2_stream_destroy(stream);
    
    if (pool) {
        apr_pool_clear(pool);
        if (session->spare) {
            apr_pool_destroy(session->spare);
        }
        session->spare = pool;
    }
    return APR_SUCCESS;
}

int h2_session_push_enabled(h2_session *session)
{
    /* iff we can and they can and want */
    return (session->remote.accepting /* remote GOAWAY received */
            && h2_config_geti(session->config, H2_CONF_PUSH)
            && nghttp2_session_get_remote_settings(session->ngh2, 
