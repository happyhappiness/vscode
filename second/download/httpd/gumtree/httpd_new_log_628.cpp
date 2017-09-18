ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Cannot allocate hash table in shared memory: %s",
                     table_strerror(ta_errno));