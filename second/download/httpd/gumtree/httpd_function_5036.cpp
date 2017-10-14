static int get_worker(int *have_idle_worker_p)
{
    apr_status_t rc;

    if (!*have_idle_worker_p) {
        rc = ap_queue_info_wait_for_idler(worker_queue_info);

        if (rc == APR_SUCCESS) {
            *have_idle_worker_p = 1;
            return 1;
        }
        else {
            if (!APR_STATUS_IS_EOF(rc)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, ap_server_conf,
                             "ap_queue_info_wait_for_idler failed.  "
                             "Attempting to shutdown process gracefully");
                signal_threads(ST_GRACEFUL);
            }
            return 0;
        }
    }
    else {
        /* already reserved a worker thread - must have hit a
         * transient error on a previous pass
         */
        return 1;
    }
}