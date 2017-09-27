     if (dmsg == NULL) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_msg_copy(): destination msg is null");
         return AJP_EINVAL;
     }
 
-    if (smsg->len > AJP_MSG_BUFFER_SZ) {
+    if (smsg->len > smsg->max_size) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_msg_copy(): destination buffer too "
-                     "small %" APR_SIZE_T_FMT ", max size is %d",
-                     smsg->len, AJP_MSG_BUFFER_SZ);
+                     "small %" APR_SIZE_T_FMT ", max size is %" APR_SIZE_T_FMT,
+                     smsg->len, smsg->max_size);
         return  AJP_ETOSMALL;
     }
 
     memcpy(dmsg->buf, smsg->buf, smsg->len);
     dmsg->len = smsg->len;
     dmsg->pos = smsg->pos;
