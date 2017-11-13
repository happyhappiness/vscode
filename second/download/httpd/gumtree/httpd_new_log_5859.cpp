ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): failed to create stream obj %d",
                      session->id, is->id, nid);