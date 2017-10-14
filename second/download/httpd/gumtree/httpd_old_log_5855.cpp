ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                      APLOGNO(02939) "h2_stream(%ld-%d): submit_response: %s",
                      session->id, response->stream_id, nghttp2_strerror(rv));