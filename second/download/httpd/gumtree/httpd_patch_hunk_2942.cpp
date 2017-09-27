      * 1                 : The CMD_AJP13_SEND_BODY_CHUNK indicator byte (0x03).
      * 1                 : The last byte of this message always seems to be
      *                     0x00 and is not part of the chunk.
      */
     expected_len = msg->len - (AJP_HEADER_LEN + AJP_HEADER_SZ_LEN + 1 + 1);
     if (*len != expected_len) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00998)
                "ajp_parse_data: Wrong chunk length. Length of chunk is %i,"
                " expected length is %i.", *len, expected_len);
         return AJP_EBAD_HEADER;
     }
     *ptr = (char *)&(msg->buf[msg->pos]);
     return APR_SUCCESS;
 }
 
+/* Check the reuse flag in CMD_AJP13_END_RESPONSE */
+apr_status_t ajp_parse_reuse(request_rec *r, ajp_msg_t *msg,
+                             apr_byte_t *reuse)
+{
+    apr_byte_t result;
+    apr_status_t rc;
+
+    rc = ajp_msg_get_uint8(msg, &result);
+    if (rc != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00999)
+               "ajp_parse_reuse: ajp_msg_get_byte failed");
+        return rc;
+    }
+    if (result != CMD_AJP13_END_RESPONSE) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01000)
+               "ajp_parse_reuse: wrong type %s (0x%02x) expecting %s (0x%02x)",
+               ajp_type_str(result), result,
+               ajp_type_str(CMD_AJP13_END_RESPONSE), CMD_AJP13_END_RESPONSE);
+        return AJP_EBAD_HEADER;
+    }
+    return ajp_msg_get_uint8(msg, reuse);
+}
+
 /*
  * Allocate a msg to send data
  */
 apr_status_t  ajp_alloc_data_msg(apr_pool_t *pool, char **ptr, apr_size_t *len,
                                  ajp_msg_t **msg)
 {
