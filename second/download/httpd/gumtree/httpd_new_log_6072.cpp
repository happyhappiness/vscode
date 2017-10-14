ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03072)
                          "h2_stream(%ld-%d): submit %d trailers",
                          session->id, (int)stream_id,(int) nh->nvlen);