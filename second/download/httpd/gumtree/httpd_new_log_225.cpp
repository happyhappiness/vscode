ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                                 "could not initialize buffered log mutex, "
                                 "transfer log may become corrupted");