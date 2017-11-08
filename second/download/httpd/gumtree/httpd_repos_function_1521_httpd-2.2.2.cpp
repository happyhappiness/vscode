apr_status_t ajp_msg_append_uint8(ajp_msg_t *msg, apr_byte_t value)
{
    apr_size_t len = msg->len;

    if ((len + 1) > AJP_MSG_BUFFER_SZ) {
        return ajp_log_overflow(msg, "ajp_msg_append_uint8");
    }

    msg->buf[len] = value;
    msg->len += 1;

    return APR_SUCCESS;
}