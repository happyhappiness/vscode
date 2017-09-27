         return AJP_EBAD_HEADER;
     }
     rc = ajp_msg_get_uint16(msg, len);
     if (rc != APR_SUCCESS) {
         return rc;
     }
+    /*
+     * msg->len contains the complete length of the message including all
+     * headers. So the expected length for a CMD_AJP13_SEND_BODY_CHUNK is
+     * msg->len minus the sum of
+     * AJP_HEADER_LEN    : The length of the header to every AJP message.
+     * AJP_HEADER_SZ_LEN : The header giving the size of the chunk.
+     * 1                 : The CMD_AJP13_SEND_BODY_CHUNK indicator byte (0x03).
+     * 1                 : The last byte of this message always seems to be
+     *                     0x00 and is not part of the chunk.
+     */
+    expected_len = msg->len - (AJP_HEADER_LEN + AJP_HEADER_SZ_LEN + 1 + 1);
+    if (*len != expected_len) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+               "ajp_parse_data: Wrong chunk length. Length of chunk is %i,"
+               " expected length is %i.", *len, expected_len);
+        return AJP_EBAD_HEADER;
+    }
     *ptr = (char *)&(msg->buf[msg->pos]);
     return APR_SUCCESS;
 }
 
 /*
  * Allocate a msg to send data
