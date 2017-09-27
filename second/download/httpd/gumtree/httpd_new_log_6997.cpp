ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03067)
                          "h2_stream(%ld-%d): RST_STREAM by client, errror=%d",
                          session->id, (int)frame->hd.stream_id,
                          (int)frame->rst_stream.error_code);