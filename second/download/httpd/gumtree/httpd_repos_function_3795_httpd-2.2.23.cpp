const char *apr_signal_description_get(int signum)
{
    return (signum >= 0) ? sys_siglist[signum] : "unknown signal (number)";
}