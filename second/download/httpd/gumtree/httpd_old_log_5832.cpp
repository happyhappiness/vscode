ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,
                      "h2_stream(%ld-%d): close error %d",
                      session->id, (int)stream_id, error_code);