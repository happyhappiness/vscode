static int h2_session_continue_data(h2_session *session) {
    if (h2_mplx_has_master_events(session->mplx)) {
        return 0;
    }
    if (h2_conn_io_needs_flush(&session->io)) {
        return 0;
    }
    return 1;
}