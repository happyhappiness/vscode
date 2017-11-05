ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      ""H2_STRM_LOG(APLOGNO(03203), stream, 
                      "PUSH %s, weight=%d, depends=%d, returned=%d"),
                      ptype, ps.weight, ps.stream_id, rv);