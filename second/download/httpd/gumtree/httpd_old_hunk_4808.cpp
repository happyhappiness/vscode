                    ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL, "Syntax OK");
            }
            destroy_and_exit_process(process, 0);
        }
    }

    signal_server = APR_RETRIEVE_OPTIONAL_FN(ap_signal_server);
    if (signal_server) {
        int exit_status;

        if (signal_server(&exit_status, pconf) != 0) {
            destroy_and_exit_process(process, exit_status);
        }
    }

    /* If our config failed, deal with that here. */
    if (rv != OK) {
        destroy_and_exit_process(process, 1);
    }

    apr_pool_clear(plog);

    if ( ap_run_open_logs(pconf, plog, ptemp, ap_server_conf) != OK) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP |APLOG_ERR,
                     0, NULL, APLOGNO(00015) "Unable to open logs");
        destroy_and_exit_process(process, 1);
