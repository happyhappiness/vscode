static int send_signal(pid_t pid, int sig)
{
    if (kill(pid, sig) < 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, errno, NULL,
                     "sending signal to server");
        return 1;
    }
    return 0;
}