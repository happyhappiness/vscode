ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): PUSH %s, weight=%d, "
                      "depends=%d, returned=%d",
                      session->id, stream->id, ptype, 
                      ps.weight, ps.stream_id, rv);