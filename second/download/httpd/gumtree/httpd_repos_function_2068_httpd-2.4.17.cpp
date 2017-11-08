int ajp_parse_type(request_rec  *r, ajp_msg_t *msg)
{
    apr_byte_t result;
    ajp_msg_peek_uint8(msg, &result);
    ap_log_rerror(APLOG_MARK, APLOG_TRACE6, 0, r,
               "ajp_parse_type: got %s (0x%02x)",
               ajp_type_str(result), result);
    return (int) result;
}