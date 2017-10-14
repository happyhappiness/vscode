ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                  H2_STRM_MSG(stream, "read_to, len=%ld eos=%d"),
                  (long)*plen, *peos);