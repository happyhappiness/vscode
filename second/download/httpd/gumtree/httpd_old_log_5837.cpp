ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, session->c,
                          "h2_stream(%ld-%d): input closed",
                          session->id, (int)frame->hd.stream_id);