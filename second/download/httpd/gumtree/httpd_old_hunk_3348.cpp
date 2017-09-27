    /* Set up an OS/2 queue for passing connections & termination requests
     * to worker threads
     */
    rc = DosCreateQueue(&workq, QUE_FIFO, apr_psprintf(pchild, "/queues/httpd/work.%d", my_pid));

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to create work queue, exiting");
        clean_child_exit(APEXIT_CHILDFATAL);
    }

    /* Create initial pool of worker threads */
    for (c = 0; c < ap_min_spare_threads; c++) {
