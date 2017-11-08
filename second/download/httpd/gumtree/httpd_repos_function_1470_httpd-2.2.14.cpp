apr_status_t ajp_ilink_receive(apr_socket_t *sock, ajp_msg_t *msg)
{
    apr_status_t status;
    apr_size_t   hlen;
    apr_size_t   blen;

    if (sock == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_ilink_receive(): NULL socket provided");
        return AJP_EINVAL;
    }

    hlen = msg->header_len;

    status = ilink_read(sock, msg->buf, hlen);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, NULL,
                     "ajp_ilink_receive() can't receive header");
        return AJP_ENO_HEADER;
    }

    status = ajp_msg_check_header(msg, &blen);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ajp_ilink_receive() received bad header");
        return AJP_EBAD_HEADER;
    }

    status = ilink_read(sock, msg->buf + hlen, blen);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, NULL,
                     "ajp_ilink_receive() error while receiving message body "
                     "of length %" APR_SIZE_T_FMT,
                     hlen);
        return AJP_EBAD_MESSAGE;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                 "ajp_ilink_receive() received packet len=%" APR_SIZE_T_FMT
                 "type=%d",
                  blen, (int)msg->buf[hlen]);

    return APR_SUCCESS;
}