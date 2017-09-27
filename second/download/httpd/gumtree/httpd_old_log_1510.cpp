ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_data: wrong type %02x expecting 0x03", result);