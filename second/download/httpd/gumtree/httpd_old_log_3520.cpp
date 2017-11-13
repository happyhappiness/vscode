ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "inserting socache entry larger (%d) than subcache data area (%d)",
                     total_len, header->subcache_data_size);