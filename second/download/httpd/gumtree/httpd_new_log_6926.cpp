ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                          H2_STRM_MSG(stream, "prepare, len=%ld eos=%d"),
                          (long)*plen, *peos);