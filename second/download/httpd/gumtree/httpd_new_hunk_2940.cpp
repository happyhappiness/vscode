    apr_byte_t result;
    apr_status_t rc;

    if (*msg) {
        rc = ajp_msg_reuse(*msg);
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00990)
                   "ajp_read_header: ajp_msg_reuse failed");
            return rc;
        }
    }
    else {
        rc = ajp_msg_create(r->pool, buffsize, msg);
        if (rc != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00991)
                   "ajp_read_header: ajp_msg_create failed");
            return rc;
        }
    }
    ajp_msg_reset(*msg);
    rc = ajp_ilink_receive(sock, *msg);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00992)
               "ajp_read_header: ajp_ilink_receive failed");
        return rc;
    }
    ajp_msg_log(r, *msg, "ajp_read_header: ajp_ilink_receive packet dump");
    rc = ajp_msg_peek_uint8(*msg, &result);
    if (rc != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00993)
                      "ajp_read_header: ajp_msg_peek_uint8 failed");
        return rc;
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
               "ajp_read_header: ajp_ilink_received %s (0x%02x)",
               ajp_type_str(result), result);
    return APR_SUCCESS;
}

/* parse the msg to read the type */
int ajp_parse_type(request_rec  *r, ajp_msg_t *msg)
{
    apr_byte_t result;
    ajp_msg_peek_uint8(msg, &result);
    ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, r,
               "ajp_parse_type: got %s (0x%02x)",
               ajp_type_str(result), result);
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
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00994)
               "ajp_parse_headers: ajp_msg_get_byte failed");
        return rc;
    }
    if (result != CMD_AJP13_SEND_HEADERS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00995)
               "ajp_parse_headers: wrong type %s (0x%02x) expecting %s (0x%02x)",
               ajp_type_str(result), result,
               ajp_type_str(CMD_AJP13_SEND_HEADERS), CMD_AJP13_SEND_HEADERS);
        return AJP_EBAD_HEADER;
    }
    return ajp_unmarshal_response(msg, r, conf);
}

/* parse the body and return data address and length */
