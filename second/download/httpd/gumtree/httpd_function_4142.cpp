apr_status_t ajp_ilink_send(apr_socket_t *sock, ajp_msg_t *msg)
{
    char         *buf;
    apr_status_t status;
    apr_size_t   length;

    if (sock == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_ilink_send(): NULL socket provided");
        return AJP_EINVAL;
    }

    ajp_msg_end(msg);

    length = msg->len;
    buf    = (char *)msg->buf;

    do {
        apr_size_t written = length;

        status = apr_socket_send(sock, buf, &written);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, NULL,
                          "ajp_ilink_send(): send failed");
            return status;
        }
        length -= written;
        buf    += written;
    } while (length);

    return APR_SUCCESS;
}