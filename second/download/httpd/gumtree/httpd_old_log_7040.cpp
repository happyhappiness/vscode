ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                  "h2_stream(%ld-%d): prepared len=%ld, eos=%d", 
                  session->id, stream->id, (long)len, eos);