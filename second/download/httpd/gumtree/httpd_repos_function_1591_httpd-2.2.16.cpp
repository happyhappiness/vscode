apr_status_t ajp_msg_append_uint16(ajp_msg_t *msg, apr_uint16_t value)
{
    apr_size_t len = msg->len;

    if ((len + 2) > msg->max_size) {
        return ajp_log_overflow(msg, "ajp_msg_append_uint16");
    }

    msg->buf[len]     = (apr_byte_t)((value >> 8) & 0xFF);
    msg->buf[len + 1] = (apr_byte_t)(value & 0xFF);

    msg->len += 2;

    return APR_SUCCESS;
}