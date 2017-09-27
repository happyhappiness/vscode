    apr_byte_t result;
    apr_status_t rc;

    if (*msg) {
        rc = ajp_msg_reuse(*msg);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_read_header: ajp_msg_reuse failed");
            return rc;
        }
    }
    else {
        rc = ajp_msg_create(r->pool, buffsize, msg);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_read_header: ajp_msg_create failed");
            return rc;
        }
    }
    ajp_msg_reset(*msg);
    rc = ajp_ilink_receive(sock, *msg);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_read_header: ajp_ilink_receive failed");
        return rc;
    }
    rc = ajp_msg_peek_uint8(*msg, &result);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_read_header: ajp_ilink_received %02x", result);
    return APR_SUCCESS;
}

/* parse the msg to read the type */
int ajp_parse_type(request_rec  *r, ajp_msg_t *msg)
{
    apr_byte_t result;
    ajp_msg_peek_uint8(msg, &result);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_parse_type: got %02x", result);
    return (int) result;
}

/* parse the header */
apr_status_t ajp_parse_header(request_rec  *r, proxy_dir_conf *conf,
                              ajp_msg_t *msg)
{
    apr_byte_t result;
    apr_status_t rc;

    rc = ajp_msg_get_uint8(msg, &result);
    if (rc != APR_SUCCESS) {
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
