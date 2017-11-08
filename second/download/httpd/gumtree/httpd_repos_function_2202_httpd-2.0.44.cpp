static void create_listener_thread(thread_starter *ts)
{
    int my_child_num = ts->child_num_arg;
    apr_threadattr_t *thread_attr = ts->threadattr;
    proc_info *my_info;
    apr_status_t rv;

    my_info = (proc_info *)malloc(sizeof(proc_info));
    my_info->pid = my_child_num;
    my_info->tid = -1; /* listener thread doesn't have a thread slot */
    my_info->sd = 0;
    rv = apr_thread_create(&ts->listener, thread_attr, listener_thread,
                           my_info, pchild);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, rv, ap_server_conf,
                     "apr_thread_create: unable to create listener thread");
        /* In case system resources are maxxed out, we don't want
         * Apache running away with the CPU trying to fork over and
         * over and over again if we exit.
         * XXX Jeff doesn't see how Apache is going to try to fork again since
         * the exit code is APEXIT_CHILDFATAL
         */
        apr_sleep(10 * APR_USEC_PER_SEC);
        clean_child_exit(APEXIT_CHILDFATAL);
    }
    apr_os_thread_get(&listener_os_thread, ts->listener);
}