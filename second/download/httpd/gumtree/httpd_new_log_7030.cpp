ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                      H2_STRM_MSG(stream, "prepared no_copy, len=%ld, eos=%d"),
                      (long)nread, eos);