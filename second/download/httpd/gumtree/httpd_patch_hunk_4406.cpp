             ap_log_rerror(APLOG_MARK, APLOG_ERR, status, session->r,
                           APLOGNO(02933) "open stream 1: %s", 
                           nghttp2_strerror(*rv));
             return status;
         }
         
-        status = h2_stream_set_request(stream, session->r);
+        status = h2_stream_set_request_rec(stream, session->r);
         if (status != APR_SUCCESS) {
             return status;
         }
         status = stream_schedule(session, stream, 1);
         if (status != APR_SUCCESS) {
             return status;
