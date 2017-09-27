apr_status_t ajp_ilink_send(apr_socket_t *sock, ajp_msg_t *msg)
{
    char         *buf;
    apr_status_t status;
    apr_size_t   length;

    ajp_msg_end(msg);

    length = msg->len;
    buf    = (char *)msg->buf;

    do {
        apr_size_t written = length;

        status = apr_socket_send(sock, buf, &written);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, NULL, APLOGNO(01029)
                          "ajp_ilink_send(): send failed");
            return status;
        }
        length -= written;
        buf    += written;
    } while (length);
