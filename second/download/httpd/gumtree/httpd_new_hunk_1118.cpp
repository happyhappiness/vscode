        rc  = ajp_msg_peek_uint16(msg, &name);
        if (rc != APR_SUCCESS) {
            return rc;
        }

        if ((name & 0XFF00) == 0XA000) {
            ajp_msg_get_uint16(msg, &name);
            stringname = long_res_header_for_sc(name);
            if (stringname == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "ajp_unmarshal_response: "
                       "No such sc (%08x)",
                       name);
