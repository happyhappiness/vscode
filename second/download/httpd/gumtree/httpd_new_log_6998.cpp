ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                              H2_SSSN_MSG(session, "on_frame_rcv %s"), buffer);