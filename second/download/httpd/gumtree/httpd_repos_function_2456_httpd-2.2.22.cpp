int ap_graceful_stop_signalled(void)
{
    /* Return true if the server is stopping for whatever reason; the
     * function is used to initiate a fast exit from the connection
     * processing loop. */
    return mpm_state == AP_MPMQ_STOPPING;
}