static int log_pid(const ap_errorlog_info *info, const char *arg,
                   char *buf, int buflen)
{
    pid_t pid = getpid();
    return apr_snprintf(buf, buflen, "%" APR_PID_T_FMT, pid);
}