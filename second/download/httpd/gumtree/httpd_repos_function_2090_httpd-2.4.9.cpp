apr_status_t ajp_msg_end(ajp_msg_t *msg)
{
    apr_size_t len = msg->len - AJP_HEADER_LEN;

    if (msg->server_side) {
        msg->buf[0] = 0x41;
        msg->buf[1] = 0x42;
    }
    else {
        msg->buf[0] = 0x12;
        msg->buf[1] = 0x34;
    }

    msg->buf[2] = (apr_byte_t)((len >> 8) & 0xFF);
    msg->buf[3] = (apr_byte_t)(len & 0xFF);

    return APR_SUCCESS;
}