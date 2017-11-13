ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                 "%s(): BufferOverflowException %" APR_SIZE_T_FMT
                 " %" APR_SIZE_T_FMT,
                 context, msg->pos, msg->len);