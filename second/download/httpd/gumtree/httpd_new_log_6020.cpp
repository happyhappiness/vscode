ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03466)
                          "h2_stream(%ld-%d): no response, RST_STREAM, err=%d",
                          session->id, stream->id, err);