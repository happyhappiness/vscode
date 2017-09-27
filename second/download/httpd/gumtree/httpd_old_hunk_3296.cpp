AP_DECLARE(void) ap_log_assert(const char *szExp, const char *szFile,
                               int nLine)
{
    char time_str[APR_CTIME_LEN];

    apr_ctime(time_str, apr_time_now());
    ap_log_error(APLOG_MARK, APLOG_CRIT, 0, NULL,
                 "[%s] file %s, line %d, assertion \"%s\" failed",
                 time_str, szFile, nLine, szExp);
#if defined(WIN32)
    DebugBreak();
#else
    /* unix assert does an abort leading to a core dump */
