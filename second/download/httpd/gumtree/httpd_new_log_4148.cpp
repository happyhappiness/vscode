ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, APLOGNO(01033)
                 "ajp_ilink_receive() received packet len=%" APR_SIZE_T_FMT
                 "type=%d",
                  blen, (int)msg->buf[hlen]);