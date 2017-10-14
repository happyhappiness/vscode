ap_log_cerror(APLOG_MARK, APLOG_ERR, status, session->c,
                      APLOGNO(02923) 
                      "h2_session: stream(%ld-%d): error handling frame",
                      session->id, (int)frame->hd.stream_id);