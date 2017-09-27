ap_log_error(APLOG_MARK, APLOG_ALERT, rv, main_server,
                         "mod_unique_id: using low-order bits of IPv6 address "
                         "as if they were unique");