static int log_tid(const ap_errorlog_info *info, const char *arg,
                   char *buf, int buflen)
{
#if APR_HAS_THREADS
    int result;
#endif
#if HAVE_GETTID
    if (arg && *arg == 'g') {
        pid_t tid = syscall(SYS_gettid);
        if (tid == -1)
            return 0;
        return apr_snprintf(buf, buflen, "%"APR_PID_T_FMT, tid);
    }
#endif
#if APR_HAS_THREADS
    if (ap_mpm_query(AP_MPMQ_IS_THREADED, &result) == APR_SUCCESS
        && result != AP_MPMQ_NOT_SUPPORTED)
    {
        apr_os_thread_t tid = apr_os_thread_current();
        return apr_snprintf(buf, buflen, "%pT", &tid);
    }
#endif
    return 0;
}