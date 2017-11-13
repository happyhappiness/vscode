ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, stream->session->c,
                      "h2_stream(%ld-%d): read_to, saving trailers",
                      stream->session->id, stream->id);