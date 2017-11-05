ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01081)
                     "ajp_msg_check_header() incoming message is "
                     "too big %" APR_SIZE_T_FMT ", max is %" APR_SIZE_T_FMT,
                     msglen, msg->max_size);