            }
            else {
                status = APR_EINVAL;
            }
            break;
        case NGHTTP2_DATA:
            stream = get_stream(session, frame->hd.stream_id);
            if (stream) {
                int eos = (frame->hd.flags & NGHTTP2_FLAG_END_STREAM);
                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
                              "h2_stream(%ld-%d): DATA, len=%ld, eos=%d", 
                              session->id, frame->hd.stream_id, 
                              (long)frame->hd.length, eos);
