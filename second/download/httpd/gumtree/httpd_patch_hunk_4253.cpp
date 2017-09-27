                           APLOGNO(02932) "nghttp2_session_upgrade: %s", 
                           nghttp2_strerror(*rv));
             return status;
         }
         
         /* Now we need to auto-open stream 1 for the request we got. */
-        stream = h2_session_open_stream(session, 1);
+        stream = h2_session_open_stream(session, 1, 0, NULL);
         if (!stream) {
             status = APR_EGENERAL;
             ap_log_rerror(APLOG_MARK, APLOG_ERR, status, session->r,
                           APLOGNO(02933) "open stream 1: %s", 
                           nghttp2_strerror(*rv));
             return status;
