ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, 
                 "Init: Created hash-table (%d buckets) "
                 "in shared memory (%" APR_SIZE_T_FMT 
                 " bytes) for SSL session cache",
                 n, avail);