/* parse the body and return data address and length */
apr_status_t  ajp_parse_data(request_rec  *r, ajp_msg_t *msg,
                             apr_uint16_t *len, char **ptr)
{
    apr_byte_t result;
    apr_status_t rc;
    apr_uint16_t expected_len;

    rc = ajp_msg_get_uint8(msg, &result);
    if (rc != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_data: ajp_msg_get_byte failed");
        return rc;
