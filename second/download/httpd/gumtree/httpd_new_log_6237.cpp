ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                  H2_STRM_MSG(stream, "prepared len=%ld, eos=%d"), 
                  (long)len, eos);