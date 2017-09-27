
    status = ilink_read(sock, msg->buf, hlen);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, NULL,
                     "ajp_ilink_receive() can't receive header");
        return (APR_STATUS_IS_TIMEUP(status) ? APR_TIMEUP : AJP_ENO_HEADER);
    }

    status = ajp_msg_check_header(msg, &blen);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
