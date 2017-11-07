ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  H2_STRM_MSG(stream, "send_data_cb for %ld bytes"),
                  (long)length);