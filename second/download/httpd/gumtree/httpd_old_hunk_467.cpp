    int threads_created = 0;
    int loops;
    int prev_threads_created;

    idle_worker_stack = worker_stack_create(pchild, ap_threads_per_child);
    if (idle_worker_stack == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, 0, ap_server_conf,
                     "worker_stack_create() failed");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    loops = prev_threads_created = 0;
    while (1) {
