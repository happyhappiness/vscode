             break;
         case NGHTTP2_RST_STREAM:
             ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03067)
                           "h2_session(%ld-%d): RST_STREAM by client, errror=%d",
                           session->id, (int)frame->hd.stream_id,
                           (int)frame->rst_stream.error_code);
-            stream = h2_session_get_stream(session, frame->hd.stream_id);
+            stream = get_stream(session, frame->hd.stream_id);
             if (stream && stream->request && stream->request->initiated_on) {
                 ++session->pushes_reset;
             }
             else {
                 ++session->streams_reset;
             }
