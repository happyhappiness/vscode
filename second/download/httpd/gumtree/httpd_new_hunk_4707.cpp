        case NGHTTP2_HEADERS:
            /* This can be HEADERS for a new stream, defining the request,
             * or HEADER may come after DATA at the end of a stream as in
             * trailers */
            stream = h2_session_stream_get(session, frame->hd.stream_id);
            if (stream) {
                rv = h2_stream_recv_frame(stream, NGHTTP2_HEADERS, frame->hd.flags);
            }
            break;
        case NGHTTP2_DATA:
            stream = h2_session_stream_get(session, frame->hd.stream_id);
            if (stream) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c,  
                              H2_STRM_LOG(APLOGNO(02923), stream, 
                              "DATA, len=%ld, flags=%d"), 
                              (long)frame->hd.length, frame->hd.flags);
                rv = h2_stream_recv_frame(stream, NGHTTP2_DATA, frame->hd.flags);
            }
            break;
        case NGHTTP2_PRIORITY:
            session->reprioritize = 1;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                          "h2_stream(%ld-%d): PRIORITY frame "
