apr_status_t ajp_msg_append_bytes(ajp_msg_t *msg, const apr_byte_t *value,
                                  apr_size_t valuelen)
{
    if (! valuelen) {
        return APR_SUCCESS; /* Shouldn't we indicate an error ? */
    }

    if ((msg->len + valuelen) > AJP_MSG_BUFFER_SZ) {
        return ajp_log_overflow(msg, "ajp_msg_append_bytes");
    }

    /* We checked for space !!  */
    memcpy(msg->buf + msg->len, value, valuelen);
    msg->len += valuelen;

    return APR_SUCCESS;
}