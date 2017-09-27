ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                      "h2_stream(%ld-%d): handled, closing", 
                      session->id, (int)stream->id);