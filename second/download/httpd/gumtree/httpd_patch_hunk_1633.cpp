         return AJP_EBAD_SIGNATURE;
     }
 
     msglen  = ((head[2] & 0xff) << 8);
     msglen += (head[3] & 0xFF);
 
-    if (msglen > AJP_MSG_BUFFER_SZ) {
+    if (msglen > msg->max_size) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_check_msg_header() incoming message is "
-                     "too big %" APR_SIZE_T_FMT ", max is %d",
-                     msglen, AJP_MSG_BUFFER_SZ);
+                     "too big %" APR_SIZE_T_FMT ", max is %" APR_SIZE_T_FMT,
+                     msglen, msg->max_size);
         return AJP_ETOBIG;
     }
 
     msg->len = msglen + AJP_HEADER_LEN;
     msg->pos = AJP_HEADER_LEN;
     *len     = msglen;
