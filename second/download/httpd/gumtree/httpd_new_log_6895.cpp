ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, session->c,
                          H2_STRM_MSG(stream, "recv DATA, len=%d: -->%s<--"), 
                          (int)len, load);