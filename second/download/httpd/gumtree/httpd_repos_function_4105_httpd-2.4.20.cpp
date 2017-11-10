static BOOL CALLBACK console_control_handler(DWORD ctrl_type)
{
    switch (ctrl_type)
    {
        case CTRL_BREAK_EVENT:
            fprintf(stderr, "Apache server restarting...\n");
            ap_signal_parent(SIGNAL_PARENT_RESTART);
            return TRUE;
        case CTRL_C_EVENT:
            fprintf(stderr, "Apache server interrupted...\n");
            /* for Interrupt signals, shut down the server.
             * Tell the system we have dealt with the signal
             * without waiting for Apache to terminate.
             */
            ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
            return TRUE;

        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            /* for Terminate signals, shut down the server.
             * Wait for Apache to terminate, but respond
             * after a reasonable time to tell the system
             * that we did attempt to shut ourself down.
             */
            fprintf(stderr, "Apache server shutdown initiated...\n");
            ap_signal_parent(SIGNAL_PARENT_SHUTDOWN);
            Sleep(30000);
            return TRUE;
    }

    /* We should never get here, but this is (mostly) harmless */
    return FALSE;
}