apr_status_t ajp_msg_append_string_ex(ajp_msg_t *msg, const char *value,
                                      int convert)
{
    size_t len;

    if (value == NULL) {
        return(ajp_msg_append_uint16(msg, 0xFFFF));
    }

    len = strlen(value);
    if ((msg->len + len + 2) > msg->max_size) {
        return ajp_log_overflow(msg, "ajp_msg_append_cvt_string");
    }

    /* ignore error - we checked once */
    ajp_msg_append_uint16(msg, (apr_uint16_t)len);

    /* We checked for space !!  */
    memcpy(msg->buf + msg->len, value, len + 1); /* including \0 */

    if (convert)   /* convert from EBCDIC if needed */
        ajp_xlate_to_ascii((char *)msg->buf + msg->len, len + 1);

    msg->len += len + 1;

    return APR_SUCCESS;
}