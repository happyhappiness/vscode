                               ap_calc_scoreboard_size(),
                               PAG_COMMIT|PAG_READ|PAG_WRITE);

        if (rc) {
            ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf, APLOGNO(00205)
                         "unable to allocate shared memory for scoreboard , exiting");
            return !OK;
        }

        ap_init_scoreboard(sb_mem);
    }

    ap_scoreboard_image->global->restart_time = apr_time_now();
