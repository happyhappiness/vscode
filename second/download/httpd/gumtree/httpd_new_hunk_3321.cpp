    start_thread_may_exit = 1;  /* tell it to give up in case it is still
                                 * trying to take over slots from a
                                 * previous generation
                                 */
    rv = apr_thread_join(&thread_rv, start_thread_id);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00478)
                     "apr_thread_join: unable to join the start " "thread");
    }
}

static void child_main(int child_num_arg)
{
