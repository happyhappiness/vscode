                     */
                    if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01571)
                                "Watchdog: Failed to create parent worker thread.");
                        return rv;
                    }
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(02976)
                            "Watchdog: Created parent worker thread (%s).", w->name);
                    wd_server_conf->parent_workers++;
                }
            }
        }
    }
    if (wd_server_conf->parent_workers) {
