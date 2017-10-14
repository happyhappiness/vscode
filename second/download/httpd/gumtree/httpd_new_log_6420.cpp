ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03073)
                      "h2_stream(%ld-%d): submit response %d, REMOTE_WINDOW_SIZE=%u",
                      session->id, stream->id, response->http_status,
                      (unsigned int)nghttp2_session_get_stream_remote_window_size(session->ngh2, stream->id));