apr_status_t ajp_parse_reuse(request_rec *r, ajp_msg_t *msg,
                             apr_byte_t *reuse)
{
    apr_byte_t result;
    apr_status_t rc;

    rc = ajp_msg_get_uint8(msg, &result);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_reuse: ajp_msg_get_byte failed");
        return rc;
    }
    if (result != CMD_AJP13_END_RESPONSE) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_reuse: wrong type 0x%02x expecting 0x%02x",
               result, CMD_AJP13_END_RESPONSE);
        return AJP_EBAD_HEADER;
    }
    return ajp_msg_get_uint8(msg, reuse);
}