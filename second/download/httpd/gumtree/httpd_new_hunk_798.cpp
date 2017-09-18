    if (idle_worker_stack == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0, ap_server_conf,
                     "worker_stack_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    worker_wakeups = (worker_wakeup_info **)
        apr_palloc(pchild, sizeof(worker_wakeup_info *) *
                   ap_threads_per_child);

    loops = prev_threads_created = 0;
    while (1) {
        for (i = 0; i < ap_threads_per_child; i++) {
            int status = ap_scoreboard_image->servers[child_num_arg][i].status;
            worker_wakeup_info *wakeup;

            if (status != SERVER_GRACEFUL && status != SERVER_DEAD) {
                continue;
            }

            wakeup = worker_wakeup_create(pchild);
            if (wakeup == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, 0,
                             ap_server_conf, "worker_wakeup_create failed");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
            worker_wakeups[threads_created] = wakeup;
            my_info = (proc_info *)malloc(sizeof(proc_info));
            if (my_info == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ALERT, errno, ap_server_conf,
                             "malloc: out of memory");
                clean_child_exit(APEXIT_CHILDFATAL);
            }
