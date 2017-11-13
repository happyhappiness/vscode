ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
                      H2_STRM_LOG(APLOGNO(03073), stream, "submit response %d, REMOTE_WINDOW_SIZE=%u"),
                      headers->status,
                      (unsigned int)nghttp2_session_get_stream_remote_window_size(session->ngh2, stream->id));