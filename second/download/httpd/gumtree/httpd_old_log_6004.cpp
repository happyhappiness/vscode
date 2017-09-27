ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): submitted response %s, rv=%d",
                      session->id, response->stream_id, 
                      response->status, rv);