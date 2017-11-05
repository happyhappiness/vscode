int ajp_parse_type(request_rec  *r, ajp_msg_t *msg)
{
    apr_byte_t result;
    ajp_msg_peek_uint8(msg, &result);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_parse_type: got %02x", result);
    return (int) result;
}