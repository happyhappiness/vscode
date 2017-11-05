ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(02920) 
                      "h2_stream(%ld-%d): on_header unknown stream",
                      session->id, (int)frame->hd.stream_id);