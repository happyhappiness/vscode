apr_status_t ajp_msg_peek_uint8(ajp_msg_t *msg, apr_byte_t *rvalue)
{
    if (msg->pos > msg->len) {
        return ajp_log_overflow(msg, "ajp_msg_peek_uint8");
    }

    *rvalue = msg->buf[msg->pos];
    return APR_SUCCESS;
}