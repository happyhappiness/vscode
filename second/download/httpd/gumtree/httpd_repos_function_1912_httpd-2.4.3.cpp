apr_status_t ajp_msg_get_uint32(ajp_msg_t *msg, apr_uint32_t *rvalue)
{
    apr_uint32_t value;

    if ((msg->pos + 3) > msg->len) {
        return ajp_log_overflow(msg, "ajp_msg_get_uint32");
    }

    value  = ((msg->buf[(msg->pos++)] & 0xFF) << 24);
    value |= ((msg->buf[(msg->pos++)] & 0xFF) << 16);
    value |= ((msg->buf[(msg->pos++)] & 0xFF) << 8);
    value |= ((msg->buf[(msg->pos++)] & 0xFF));

    *rvalue = value;
    return APR_SUCCESS;
}