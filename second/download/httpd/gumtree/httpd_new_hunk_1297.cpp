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

/* XXX under some circumstances not understood, children can get stuck
 *     in start_threads forever trying to take over slots which will
