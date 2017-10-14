ap_log_error(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, ap_server_conf, APLOGNO(00408)
                     "Parent: Duplicating socket %d (%pI) and sending it to child process %lu",
                     nsd, lr->bind_addr, dwProcessId);