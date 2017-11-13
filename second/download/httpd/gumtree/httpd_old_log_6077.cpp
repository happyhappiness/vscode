ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): lookup of nghttp2_stream failed",
                      session->id, stream->id);