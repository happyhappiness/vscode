ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, p, APLOGNO(02640)
                            "ap_duplicate_listeners: for address %pI, "
                            "cannot duplicate a new socket!",
                            duplr->bind_addr);