ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, 
                 "Init: Created hash-table (%d buckets) "
                 "in shared memory (%d bytes) for SSL session cache",
                 n, avail);