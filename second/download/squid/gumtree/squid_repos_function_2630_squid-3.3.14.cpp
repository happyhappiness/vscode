void
logsFlush(void)
{
    if (debug_log)
        fflush(debug_log);
}