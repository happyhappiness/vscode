ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                      H2_STRM_MSG(stream, "writing frame header"));