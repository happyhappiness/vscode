                     */
                    if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01571)
                                "Watchdog: Failed to create parent worker thread.");
                        return rv;
                    }
                    wd_server_conf->parent_workers++;
                }
            }
        }
    }
    if (wd_server_conf->parent_workers) {
