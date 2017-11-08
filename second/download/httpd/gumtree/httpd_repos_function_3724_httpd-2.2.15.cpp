const char *apr_signal_description_get(int signum)
{
    return
        (signum >= 0 && signum < APR_NUMSIG)
        ? signal_description[signum]
        : "unknown signal (number)";
}