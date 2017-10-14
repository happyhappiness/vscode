ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, stream->session->c,
                  "h2_stream(%ld-%d): beam_received",
                  stream->session->id, stream->id);