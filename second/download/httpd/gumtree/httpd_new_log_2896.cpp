ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "inserting session larger (%d) than subcache data area (%d)",
                     data_len, header->subcache_data_size);