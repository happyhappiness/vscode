ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): on_frame_rcv #%ld, type=%d", 
                  session->id, frame->hd.stream_id, 
                  (long)session->frames_received, frame->hd.type);