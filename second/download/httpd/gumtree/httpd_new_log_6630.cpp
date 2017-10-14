ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                      "h2-stream(%ld-%d): on_header, reset stream",
                      session->id, stream->id);