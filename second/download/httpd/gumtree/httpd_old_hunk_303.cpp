    return av;
}

#if APR_HAS_OTHER_CHILD
static void cgid_maint(int reason, void *data, apr_wait_t status)
{
    pid_t *sd = data;

    switch (reason) {
        case APR_OC_REASON_DEATH:
        case APR_OC_REASON_RESTART:
            /* don't do anything; server is stopping or restarting */
            apr_proc_other_child_unregister(data);
            break;
        case APR_OC_REASON_LOST:
            /* it would be better to restart just the cgid child
             * process but for now we'll gracefully restart the entire 
             * server by sending AP_SIG_GRACEFUL to ourself, the httpd 
             * parent process
             */
            kill(getpid(), AP_SIG_GRACEFUL);
            break;
        case APR_OC_REASON_UNREGISTER:
            /* we get here when pcgi is cleaned up; pcgi gets cleaned
             * up when pconf gets cleaned up
             */
            kill(*sd, SIGHUP); /* send signal to daemon telling it to die */
            break;
    }
}
#endif

/* deal with incomplete reads and signals
