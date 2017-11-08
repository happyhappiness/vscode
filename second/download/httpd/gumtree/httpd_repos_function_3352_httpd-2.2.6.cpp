const char *apr_signal_description_get(int signum)
{
    return sys_siglist[signum];
}