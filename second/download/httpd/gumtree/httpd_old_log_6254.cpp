ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, stream->session->c,
                  "h2_stream(%ld-%d): invalid state transition from %d to %d", 
                  stream->session->id, stream->id, stream->state, state);