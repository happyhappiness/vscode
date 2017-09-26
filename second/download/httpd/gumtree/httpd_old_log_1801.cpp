ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ajp_msg_copy(): destination buffer too "
                     "small %" APR_SIZE_T_FMT ", max size is %d",
                     smsg->len, AJP_MSG_BUFFER_SZ);