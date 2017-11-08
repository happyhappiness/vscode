apr_status_t ajp_msg_reuse(ajp_msg_t *msg)
{
    apr_byte_t *buf;

    buf = msg->buf;
    memset(msg, 0, sizeof(ajp_msg_t));
    msg->buf = buf;
    msg->header_len = AJP_HEADER_LEN;
    ajp_msg_reset(msg);
    return APR_SUCCESS;
}