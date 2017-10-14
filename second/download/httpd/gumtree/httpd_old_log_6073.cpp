ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): submit response %d",
                      session->id, stream->id, response->http_status);