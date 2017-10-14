ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, session->c,
                              APLOGNO(02921) 
                              "h2_session:  stream(%ld-%d): HEADERS frame "
                              "for unknown stream", session->id,
                              (int)frame->hd.stream_id);