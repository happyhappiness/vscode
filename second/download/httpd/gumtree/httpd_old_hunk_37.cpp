    if (idle_worker_stack == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
                     "worker_stack_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    loops = prev_threads_created = 0;
    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int status = ap_scoreboard_image->servers[child_num_arg][i].status;

            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }

            my_info = (proc_info *)malloc(sizeof(proc_info));
            if (my_info == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
                             "malloc: out of memory");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
