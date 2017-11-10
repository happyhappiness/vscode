static void ap_start_shutdown(void)
{
    /* If the user tries to shut us down twice in quick succession then we
     * may well get triggered while we are working through previous attempt
     * to shutdown. We won't worry about even reporting it as it seems a little
     * pointless.
     */
    if (shutdown_pending == 1)
        return;

    shutdown_pending = 1;
}