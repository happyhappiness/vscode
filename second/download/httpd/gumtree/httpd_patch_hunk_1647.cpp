         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                "ajp_parse_data: ajp_msg_get_byte failed");
         return rc;
     }
     if (result != CMD_AJP13_SEND_BODY_CHUNK) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
-               "ajp_parse_data: wrong type 0x%02x expecting 0x%02x",
-               result, CMD_AJP13_SEND_BODY_CHUNK);
+               "ajp_parse_data: wrong type %02x expecting 0x03", result);
         return AJP_EBAD_HEADER;
     }
     rc = ajp_msg_get_uint16(msg, len);
     if (rc != APR_SUCCESS) {
         return rc;
     }
