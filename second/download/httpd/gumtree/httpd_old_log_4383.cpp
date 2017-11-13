ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                             "proxy: FCGI: Failed to read entire header "
                             "got %" APR_SIZE_T_FMT " wanted %d", 
                             readbuflen, FCGI_HEADER_LEN);