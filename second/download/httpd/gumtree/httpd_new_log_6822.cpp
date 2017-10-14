ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_stream(%ld-%d): WINDOW_UPDATE incr=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->window_update.window_size_increment);