apr_status_t ajp_msg_append_uint32(ajp_msg_t *msg, apr_uint32_t value)
{
    apr_size_t len = msg->len;

    if ((len + 4) > msg->max_size) {
        return ajp_log_overflow(msg, "ajp_msg_append_uint32");
    }

    msg->buf[len]     = (apr_byte_t)((value >> 24) & 0xFF);
    msg->buf[len + 1] = (apr_byte_t)((value >> 16) & 0xFF);
    msg->buf[len + 2] = (apr_byte_t)((value >> 8) & 0xFF);
    msg->buf[len + 3] = (apr_byte_t)(value & 0xFF);

    msg->len += 4;

    return APR_SUCCESS;
}