static void server_maintenance(void *vpArg)
{
    int num_idle, num_needed;
    ULONG num_pending = 0;
    int threadnum;
    HQUEUE workq;
    ULONG rc;
    PID owner;

    rc = DosOpenQueue(&owner, &workq,
                      apr_psprintf(pchild, "/queues/httpd/work.%d", getpid()));

    if (rc) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_FROM_OS_ERROR(rc), ap_server_conf,
                     "unable to open work queue in maintenance thread");
        return;
    }

    do {
        for (num_idle=0, threadnum=0; threadnum < HARD_THREAD_LIMIT; threadnum++) {
            num_idle += ap_scoreboard_image->servers[child_slot][threadnum].status == SERVER_READY;
        }

        DosQueryQueue(workq, &num_pending);
        num_needed = ap_min_spare_threads - num_idle + num_pending;

        if (num_needed > 0) {
            for (threadnum=0; threadnum < num_needed; threadnum++) {
                add_worker();
            }
        }

        if (num_idle - num_pending > ap_max_spare_threads) {
            DosWriteQueue(workq, WORKTYPE_EXIT, 0, NULL, 0);
        }
    } while (DosWaitEventSem(shutdown_event, 500) == ERROR_TIMEOUT);
}