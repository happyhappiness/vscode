static void worker_main(void *vpArg)
{
    long conn_id;
    conn_rec *current_conn;
    apr_pool_t *pconn;
    apr_allocator_t *allocator;
    apr_bucket_alloc_t *bucket_alloc;
    worker_args_t *worker_args;
    HQUEUE workq;
    PID owner;
    int rc;
    REQUESTDATA rd;
    ULONG len;
    BYTE priority;
    int thread_slot = (int)vpArg;
    EXCEPTIONREGISTRATIONRECORD reg_rec = { NULL, thread_exception_handler };
    ap_sb_handle_t *sbh;

    /* Trap exceptions in this thread so we don't take down the whole process */
    DosSetExceptionHandler( &reg_rec );

    rc = DosOpenQueue(&owner, &workq,
                      apr_psprintf(pchild, "/queues/httpd/work.%d", getpid()));

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to open work queue, exiting");
        ap_scoreboard_image->servers[child_slot][thread_slot].tid = 0;
    }

    conn_id = ID_FROM_CHILD_THREAD(child_slot, thread_slot);
    ap_update_child_status_from_indexes(child_slot, thread_slot, SERVER_READY,
                                        NULL);

    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    bucket_alloc = apr_bucket_alloc_create_ex(allocator);

    while (rc = DosReadQueue(workq, &rd, &len, (PPVOID)&worker_args, 0, DCWW_WAIT, &priority, NULLHANDLE),
           rc == 0 && rd.ulData != WORKTYPE_EXIT) {
        pconn = worker_args->pconn;
        ap_create_sb_handle(&sbh, pconn, child_slot, thread_slot);
        current_conn = ap_run_create_connection(pconn, ap_server_conf,
                                                worker_args->conn_sd, conn_id,
                                                sbh, bucket_alloc);

        if (current_conn) {
            ap_process_connection(current_conn, worker_args->conn_sd);
            ap_lingering_close(current_conn);
        }

        apr_pool_destroy(pconn);
        ap_update_child_status_from_indexes(child_slot, thread_slot,
                                            SERVER_READY, NULL);
    }

    ap_update_child_status_from_indexes(child_slot, thread_slot, SERVER_DEAD,
                                        NULL);

    apr_bucket_alloc_destroy(bucket_alloc);
    apr_allocator_destroy(allocator);
}