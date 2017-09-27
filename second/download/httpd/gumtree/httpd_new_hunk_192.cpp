    return av;
}

#if APR_HAS_OTHER_CHILD
static void cgid_maint(int reason, void *data, apr_wait_t status)
{
    apr_proc_t *proc = data;
    int mpm_state;
    int stopping;

    switch (reason) {
        case APR_OC_REASON_DEATH:
            apr_proc_other_child_unregister(data);
            /* If apache is not terminating or restarting,
             * restart the cgid daemon
             */
            stopping = 1; /* if MPM doesn't support query,
                           * assume we shouldn't restart daemon
                           */
            if (ap_mpm_query(AP_MPMQ_MPM_STATE, &mpm_state) == APR_SUCCESS &&
                mpm_state != AP_MPMQ_STOPPING) {
                stopping = 0;
            }
            if (!stopping) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                             "cgid daemon process died, restarting");
                cgid_start(root_pool, root_server, proc);
            }
            break;
        case APR_OC_REASON_RESTART:
            /* don't do anything; server is stopping or restarting */
            apr_proc_other_child_unregister(data);
            break;
        case APR_OC_REASON_LOST:
            /* Restart the child cgid daemon process */
            apr_proc_other_child_unregister(data);
            cgid_start(root_pool, root_server, proc);
            break;
        case APR_OC_REASON_UNREGISTER:
            /* we get here when pcgi is cleaned up; pcgi gets cleaned
             * up when pconf gets cleaned up
             */
            kill(proc->pid, SIGHUP); /* send signal to daemon telling it to die */
            break;
    }
}
#endif

/* deal with incomplete reads and signals
