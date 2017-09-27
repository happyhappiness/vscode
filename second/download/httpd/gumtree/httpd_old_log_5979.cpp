ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                  "h2_session(%ld): on_frame_rcv #%ld, type=%d", session->id,
                  (long)session->frames_received, frame->hd.type);