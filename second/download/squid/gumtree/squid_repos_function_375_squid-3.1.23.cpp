static void
rfcnb_alarm(int sig)
{
    syslog(LOG_ERR, "%s:%d: IO Timed out ...\n", __FILE__, __LINE__);
}