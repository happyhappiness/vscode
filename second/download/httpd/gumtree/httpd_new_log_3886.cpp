ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01067)
                              "Failed to read entire header "
                              "got %" APR_SIZE_T_FMT " wanted %d",
                              readbuflen, FCGI_HEADER_LEN);