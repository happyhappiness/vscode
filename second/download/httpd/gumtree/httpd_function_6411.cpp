static void h2_session_destroy(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    h2_session_cleanup(session);

    if (APLOGctrace1(session->c)) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      "h2_session(%ld): destroy, %d streams open",
                      session->id, (int)h2_ihash_count(session->streams));
    }
    if (session->mplx) {
        h2_mplx_set_consumed_cb(session->mplx, NULL, NULL);
        h2_mplx_release_and_join(session->mplx, session->iowait);
        session->mplx = NULL;
    }
    if (session->pool) {
        apr_pool_destroy(session->pool);
    }
}