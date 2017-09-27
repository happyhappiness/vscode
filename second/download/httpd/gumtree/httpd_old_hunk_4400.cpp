        case NGHTTP2_RST_STREAM:
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03067)
                          "h2_session(%ld-%d): RST_STREAM by client, errror=%d",
                          session->id, (int)frame->hd.stream_id,
                          (int)frame->rst_stream.error_code);
            stream = get_stream(session, frame->hd.stream_id);
            if (stream && stream->request && stream->request->initiated_on) {
                ++session->pushes_reset;
            }
            else {
                ++session->streams_reset;
            }
            break;
        case NGHTTP2_GOAWAY:
            session->remote.accepted_max = frame->goaway.last_stream_id;
            session->remote.error = frame->goaway.error_code;
            dispatch_event(session, H2_SESSION_EV_REMOTE_GOAWAY, 0, NULL);
            break;
        default:
            if (APLOGctrace2(session->c)) {
                char buffer[256];
                
                h2_util_frame_print(frame, buffer,
