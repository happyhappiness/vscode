void h2_session_destroy(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    if (session->mplx) {
        h2_mplx_release_and_join(session->mplx, session->iowait);
        session->mplx = NULL;
    }
    if (session->streams) {
        if (h2_stream_set_size(session->streams)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session(%ld): destroy, %d streams open",
                          session->id, (int)h2_stream_set_size(session->streams));
        }
        h2_stream_set_destroy(session->streams);
        session->streams = NULL;
    }
    if (session->ngh2) {
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
    }
    h2_conn_io_destroy(&session->io);
    
    if (session->iowait) {
        apr_thread_cond_destroy(session->iowait);
        session->iowait = NULL;
    }
    
    if (session->pool) {
        apr_pool_destroy(session->pool);
    }
}