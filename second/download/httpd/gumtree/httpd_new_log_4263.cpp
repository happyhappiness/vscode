ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, APLOGNO(01082)
                     "ajp_msg_copy(): destination buffer too "
                     "small %" APR_SIZE_T_FMT ", max size is %" APR_SIZE_T_FMT,
                     smsg->len, smsg->max_size);