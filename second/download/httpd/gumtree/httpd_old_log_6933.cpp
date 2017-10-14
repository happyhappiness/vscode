ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, stream->session->c,
                      "h2_stream(%ld-%d): found %d push candidates",
                      stream->session->id, stream->id, pushes->nelts);