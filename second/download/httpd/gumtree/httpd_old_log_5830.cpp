ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): closing with err=%d %s", 
                      session->id, (int)stream->id, (int)error_code,
                      nghttp2_strerror(error_code));