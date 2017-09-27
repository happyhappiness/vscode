     apr_byte_t result;
     apr_status_t rc;
     apr_uint16_t expected_len;
 
     rc = ajp_msg_get_uint8(msg, &result);
     if (rc != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00996)
                "ajp_parse_data: ajp_msg_get_byte failed");
         return rc;
     }
     if (result != CMD_AJP13_SEND_BODY_CHUNK) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-               "ajp_parse_data: wrong type %02x expecting 0x03", result);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00997)
+               "ajp_parse_data: wrong type %s (0x%02x) expecting %s (0x%02x)",
+               ajp_type_str(result), result,
+               ajp_type_str(CMD_AJP13_SEND_BODY_CHUNK), CMD_AJP13_SEND_BODY_CHUNK);
         return AJP_EBAD_HEADER;
     }
     rc = ajp_msg_get_uint16(msg, len);
     if (rc != APR_SUCCESS) {
         return rc;
     }
