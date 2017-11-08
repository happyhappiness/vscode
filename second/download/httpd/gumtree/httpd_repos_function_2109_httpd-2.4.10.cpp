apr_status_t ajp_msg_peek_uint16(ajp_msg_t *msg, apr_uint16_t *rvalue)
{
    apr_uint16_t value;

    if ((msg->pos + 1) > msg->len) {
        return ajp_log_overflow(msg, "ajp_msg_peek_uint16");
    }

    value = ((msg->buf[(msg->pos)] & 0xFF) << 8);
    value += ((msg->buf[(msg->pos + 1)] & 0xFF));

    *rvalue = value;
    return APR_SUCCESS;
}