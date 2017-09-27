         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(03361)
                      "h2_proxy_stream(%s): data_read, stream %d not found", 
                      stream->session->id, stream_id);
         return NGHTTP2_ERR_CALLBACK_FAILURE;
     }
     
-    if (APR_BRIGADE_EMPTY(stream->input)) {
+    if (stream->session->check_ping) {
+        /* suspend until we hear from the other side */
+        stream->waiting_on_ping = 1;
+        status = APR_EAGAIN;
+    }
+    else if (stream->r->expecting_100) {
+        /* suspend until the answer comes */
+        stream->waiting_on_100 = 1;
+        status = APR_EAGAIN;
+    }
+    else if (APR_BRIGADE_EMPTY(stream->input)) {
         status = ap_get_brigade(stream->r->input_filters, stream->input,
                                 AP_MODE_READBYTES, APR_NONBLOCK_READ,
                                 H2MAX(APR_BUCKET_BUFF_SIZE, length));
         ap_log_rerror(APLOG_MARK, APLOG_TRACE2, status, stream->r, 
                       "h2_proxy_stream(%s-%d): request body read", 
                       stream->session->id, stream->id);
