static void h2_session_cleanup(h2_session *session)
{
    AP_DEBUG_ASSERT(session);
    /* This is an early cleanup of the session that may
     * discard what is no longer necessary for *new* streams
     * and general HTTP/2 processing.
     * At this point, all frames are in transit or somehwere in
     * our buffers or passed down output filters.
     * h2 streams might still being written out.
     */
    if (session->ngh2) {
        nghttp2_session_del(session->ngh2);
        session->ngh2 = NULL;
    }
    if (session->spare) {
        apr_pool_destroy(session->spare);
        session->spare = NULL;
    }
}