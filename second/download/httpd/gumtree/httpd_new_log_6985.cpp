ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, server,
                         "%s: reusing backend connection %pI<>%pI",
                         scheme, local_addr, conn->addr);