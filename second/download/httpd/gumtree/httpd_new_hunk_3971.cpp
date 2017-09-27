                if ((rv = wd_startup(w, wd_server_conf->pool)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01573)
                                 "Watchdog: Failed to create worker thread.");
                    /* No point to continue */
                    return;
                }
                ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(02981)
                             "Watchdog: Created worker thread (%s).", wn[i].provider_name);
            }
        }
    }
}

/*--------------------------------------------------------------------------*/
