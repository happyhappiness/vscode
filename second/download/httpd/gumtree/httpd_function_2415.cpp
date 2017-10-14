static int reclaim_one_pid(pid_t pid, action_t action)
{
    apr_proc_t proc;
    apr_status_t waitret;

    /* Ensure pid sanity. */
    if (pid < 1) {
        return 1;
    }        

    proc.pid = pid;
    waitret = apr_proc_wait(&proc, NULL, NULL, APR_NOWAIT);
    if (waitret != APR_CHILD_NOTDONE) {
        return 1;
    }

    switch(action) {
    case DO_NOTHING:
        break;

    case SEND_SIGTERM:
        /* ok, now it's being annoying */
        ap_log_error(APLOG_MARK, APLOG_WARNING,
                     0, ap_server_conf,
                     "child process %" APR_PID_T_FMT
                     " still did not exit, "
                     "sending a SIGTERM",
                     pid);
        kill(pid, SIGTERM);
        break;

    case SEND_SIGKILL:
        ap_log_error(APLOG_MARK, APLOG_ERR,
                     0, ap_server_conf,
                     "child process %" APR_PID_T_FMT
                     " still did not exit, "
                     "sending a SIGKILL",
                     pid);
#ifndef BEOS
        kill(pid, SIGKILL);
#else
        /* sending a SIGKILL kills the entire team on BeOS, and as
         * httpd thread is part of that team it removes any chance
         * of ever doing a restart.  To counter this I'm changing to
         * use a kinder, gentler way of killing a specific thread
         * that is just as effective.
         */
        kill_thread(pid);
#endif
        break;

    case GIVEUP:
        /* gave it our best shot, but alas...  If this really
         * is a child we are trying to kill and it really hasn't
         * exited, we will likely fail to bind to the port
         * after the restart.
         */
        ap_log_error(APLOG_MARK, APLOG_ERR,
                     0, ap_server_conf,
                     "could not make child process %" APR_PID_T_FMT
                     " exit, "
                     "attempting to continue anyway",
                     pid);
        break;
    }

    return 0;
}