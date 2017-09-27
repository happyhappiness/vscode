ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ajp_check_msg_header() incoming message is "
                     "too big %" APR_SIZE_T_FMT ", max is %d",
                     msglen, AJP_MSG_BUFFER_SZ);