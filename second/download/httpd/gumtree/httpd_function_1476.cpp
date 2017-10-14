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