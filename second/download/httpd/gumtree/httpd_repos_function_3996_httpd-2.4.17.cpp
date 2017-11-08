static void get_worker(int *have_idle_worker_p, int blocking, int *all_busy)
{
    apr_status_t rc;

    if (*have_idle_worker_p) {
        /* already reserved a worker thread - must have hit a
         * transient error on a previous pass
         */
        return;
    }

    if (blocking)
        rc = ap_queue_info_wait_for_idler(worker_queue_info, all_busy);
    else
        rc = ap_queue_info_try_get_idler(worker_queue_info);

    if (rc == APR_SUCCESS || APR_STATUS_IS_EOF(rc)) {
        *have_idle_worker_p = 1;
    }
    else if (!blocking && rc == APR_EAGAIN) {
        *all_busy = 1;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf, APLOGNO(00472)
                     "ap_queue_info_wait_for_idler failed.  "
                     "Attempting to shutdown process gracefully");
        signal_threads(ST_GRACEFUL);
    }
}