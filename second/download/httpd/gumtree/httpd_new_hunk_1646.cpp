        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_headers: ajp_msg_get_byte failed");
        return rc;
    }
    if (result != CMD_AJP13_SEND_HEADERS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_headers: wrong type %02x expecting 0x04", result);
        return AJP_EBAD_HEADER;
    }
    return ajp_unmarshal_response(msg, r, conf);
}

/* parse the body and return data address and length */
