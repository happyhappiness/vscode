ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                          H2_STRM_MSG(stream, "pseudo %s too long"), name);