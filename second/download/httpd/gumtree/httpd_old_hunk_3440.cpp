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
        /* let the parent decide how bad this really is */
        clean_child_exit(APEXIT_CHILDSICK);
    }
    apr_os_thread_get(&listener_os_thread, ts->listener);
}
