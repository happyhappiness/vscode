const char *apr_signal_description_get(int signum)
{
    return
        signum < APR_NUMSIG
        ? signal_description[signum]
        : "unknown signal (number)";
}