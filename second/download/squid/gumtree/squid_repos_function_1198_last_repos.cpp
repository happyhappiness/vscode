static void
OnTerminate()
{
    // ignore recursive calls to avoid termination loops
    static bool terminating = false;
    if (terminating)
        return;
    terminating = true;

    debugs(1, DBG_CRITICAL, "FATAL: Dying from an exception handling failure; exception: " << CurrentException);
    abort();
}