                if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01573)
                                 "Watchdog: Failed to create worker thread.");
                    /* No point to continue */
                    return;
                }
            }
        }
    }
}

/*--------------------------------------------------------------------------*/
