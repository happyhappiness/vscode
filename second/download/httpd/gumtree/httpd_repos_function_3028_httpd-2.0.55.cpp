const char *apr_signal_get_description(int signum)
{
    return apr_signal_description_get(signum);
}