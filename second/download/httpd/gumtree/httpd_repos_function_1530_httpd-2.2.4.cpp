apr_status_t ajp_msg_get_string(ajp_msg_t *msg, const char **rvalue)
{
    apr_uint16_t size;
    apr_size_t   start;
    apr_status_t status;

    status = ajp_msg_get_uint16(msg, &size);
    start = msg->pos;

    if ((status != APR_SUCCESS) || (size + start > AJP_MSG_BUFFER_SZ)) {
        return ajp_log_overflow(msg, "ajp_msg_get_string");
    }

    msg->pos += (apr_size_t)size;
    msg->pos++;                   /* a String in AJP is NULL terminated */

    *rvalue = (const char *)(msg->buf + start);
    return APR_SUCCESS;
}