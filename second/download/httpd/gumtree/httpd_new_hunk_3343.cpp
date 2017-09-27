        void *sb_mem;
        rc = DosAllocSharedMem(&sb_mem, ap_scoreboard_fname,
                               ap_calc_scoreboard_size(),
                               PAG_COMMIT|PAG_READ|PAG_WRITE);

        if (rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00205)
                         "unable to allocate shared memory for scoreboard , exiting");
            return FALSE;
        }

        ap_init_scoreboard(sb_mem);
    }

    ap_scoreboard_image->global->restart_time = apr_time_now();
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00206)
                "%s configured -- resuming normal operations",
                ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00207)
                "Server built: %s", ap_get_server_built());
    if (one_process) {
        ap_scoreboard_image->parent[0].pid = getpid();
        ap_mpm_child_main(pconf);
        return FALSE;
    }
