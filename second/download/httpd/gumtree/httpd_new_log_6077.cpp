ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, session->c,
                          "h2_stream(%ld-%d): scheduling push stream",
                          session->id, stream->id);