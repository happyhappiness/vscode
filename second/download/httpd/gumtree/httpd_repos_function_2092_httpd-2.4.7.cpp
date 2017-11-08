apr_status_t ajp_msg_reuse(ajp_msg_t *msg)
{
    apr_byte_t *buf;
    apr_size_t max_size;

    buf = msg->buf;
    max_size = msg->max_size;
    memset(msg, 0, sizeof(ajp_msg_t));
    msg->buf = buf;
    msg->max_size = max_size;
    msg->header_len = AJP_HEADER_LEN;
    ajp_msg_reset(msg);
    return APR_SUCCESS;
}