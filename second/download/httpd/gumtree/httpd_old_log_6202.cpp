ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                      "h2_session: callback on_invalid_frame_recv error=%d %s",
                      error, buffer);