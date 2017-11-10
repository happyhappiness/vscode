int ap_graceful_stop_signalled(void)
    /* XXX this is really a bad confusing obsolete name
     * maybe it should be ap_mpm_process_exiting?
     */
{
    /* note: for a graceful termination, listener_may_exit will be set before
     *       workers_may_exit, so check listener_may_exit
     */
    return listener_may_exit;
}