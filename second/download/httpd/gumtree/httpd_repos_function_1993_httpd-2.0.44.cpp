static BOOL CALLBACK child_control_handler(DWORD ctrl_type)
{
    switch (ctrl_type)
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
            /* for Interrupt signals, ignore them.
             * The system will also signal the parent process,
             * which will terminate Apache.
             */
            return TRUE;

        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            /* for Shutdown signals, ignore them, but...             .
             * The system will also signal the parent process,
             * which will terminate Apache, so we need to wait.
             */
            Sleep(30000);
            return TRUE;
    }
 
    /* We should never get here, but this is (mostly) harmless */
    return FALSE;
}