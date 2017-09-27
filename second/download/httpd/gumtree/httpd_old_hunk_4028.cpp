            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_session:  stream(%ld-%d): WINDOW_UPDATE "
                          "incr=%d", 
                          session->id, (int)frame->hd.stream_id,
                          frame->window_update.window_size_increment);
            break;
        default:
            if (APLOGctrace2(session->c)) {
                char buffer[256];
                
                frame_print(frame, buffer,
                            sizeof(buffer)/sizeof(buffer[0]));
                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                              "h2_session: on_frame_rcv %s", buffer);
            }
            break;
    }

