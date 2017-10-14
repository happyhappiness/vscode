ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog,
                         "No Listen directive found for upgradeable listener %s:%d", slu->addr, slu->port);