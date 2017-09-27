            if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state) == APR_SUCCESS &&
                mpm_state != AP_MPMQ_STOPPING) {
                stopping = 0;
            }
            if (!stopping) {
                if (status == DAEMON_STARTUP_ERROR) {
                    ap_log_error(APLOG_MARK, APLOG_CRIT, 0, ap_server_conf, APLOGNO(01238)
                                 "cgid daemon failed to initialize");
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(01239)
                                 "cgid daemon process died, restarting");
                    cgid_start(root_pool, root_server, proc);
                }
            }
            break;
        case APR_OC_REASON_RESTART:
