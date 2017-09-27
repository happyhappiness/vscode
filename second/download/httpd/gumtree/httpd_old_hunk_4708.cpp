                                    sizeof(buffer)/sizeof(buffer[0]));
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                              H2_SSSN_MSG(session, "on_frame_rcv %s"), buffer);
            }
            break;
    }
    return 0;
}

static int h2_session_continue_data(h2_session *session) {
    if (h2_mplx_has_master_events(session->mplx)) {
        return 0;
    }
