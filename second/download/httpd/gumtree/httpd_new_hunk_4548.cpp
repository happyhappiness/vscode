#ifdef H2_NG2_INVALID_HEADER_CB
    NGH2_SET_CALLBACK(*pcb, on_invalid_header, on_invalid_header_cb);
#endif
    return APR_SUCCESS;
}

static apr_status_t h2_session_shutdown_notice(h2_session *session)
{
    apr_status_t status;
    
    ap_assert(session);
    if (!session->local.accepting) {
