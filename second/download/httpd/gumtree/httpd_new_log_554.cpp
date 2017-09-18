ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                 "Inter-Process Session Cache (DBM) Expiry: "
                 "old: %d, new: %d, removed: %d",
                 nElements, nElements-nDeleted, nDeleted);