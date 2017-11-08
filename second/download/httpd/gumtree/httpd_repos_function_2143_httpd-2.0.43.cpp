static int start_thread(void)
{
    apr_thread_t *thread;
    int rc;

    apr_thread_mutex_lock(worker_thread_count_mutex);
    if (worker_thread_count < max_threads - 1) {
        rc = apr_thread_create(&thread, worker_thread_attr, worker_thread,
                 &worker_thread_free_ids[worker_thread_count], pchild);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ALERT, rc, ap_server_conf,
                         "apr_thread_create: unable to create worker thread");
            /* In case system resources are maxxed out, we don't want
               Apache running away with the CPU trying to fork over and
               over and over again if we exit. */
            sleep(10);
            workers_may_exit = 1;
            apr_thread_mutex_unlock(worker_thread_count_mutex);
            return 0;
        }
        else {
            worker_thread_count++;
        }
    }
    else {
        static int reported = 0;
        
        if (!reported) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                         ap_server_conf,
                         "server reached MaxThreadsPerChild setting, "
                         "consider raising the MaxThreadsPerChild or "
                         "NumServers settings");
            reported = 1;
        }
        apr_thread_mutex_unlock(worker_thread_count_mutex);
        return 0;
    }
    apr_thread_mutex_unlock(worker_thread_count_mutex);
    return 1;

}