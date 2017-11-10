apr_status_t ajp_msg_get_bytes(ajp_msg_t *msg, apr_byte_t **rvalue,
                               apr_size_t *rvalue_len)
{
    apr_uint16_t size;
    apr_size_t   start;
    apr_status_t status;

    status = ajp_msg_get_uint16(msg, &size);
    /* save the current position */
    start = msg->pos;

    if ((status != APR_SUCCESS) || (size + start > AJP_MSG_BUFFER_SZ)) {
        return ajp_log_overflow(msg, "ajp_msg_get_bytes");
    }
    msg->pos += (apr_size_t)size;   /* only bytes, no trailer */

    *rvalue     = msg->buf + start;
    *rvalue_len = size;

    return APR_SUCCESS;
}