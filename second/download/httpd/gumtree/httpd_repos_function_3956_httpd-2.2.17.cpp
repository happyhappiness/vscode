apr_status_t apr_strftime(char *s, apr_size_t *retsize, apr_size_t max, 
                        const char *format, apr_time_exp_t *xt)
{
    struct tm tm;
    memset(&tm, 0, sizeof tm);
    tm.tm_sec  = xt->tm_sec;
    tm.tm_min  = xt->tm_min;
    tm.tm_hour = xt->tm_hour;
    tm.tm_mday = xt->tm_mday;
    tm.tm_mon  = xt->tm_mon;
    tm.tm_year = xt->tm_year;
    tm.tm_wday = xt->tm_wday;
    tm.tm_yday = xt->tm_yday;
    tm.tm_isdst = xt->tm_isdst;
#if defined(HAVE_STRUCT_TM_TM_GMTOFF)
    tm.tm_gmtoff = xt->tm_gmtoff;
#elif defined(HAVE_STRUCT_TM___TM_GMTOFF)
    tm.__tm_gmtoff = xt->tm_gmtoff;
#endif
    (*retsize) = strftime(s, max, format, &tm);
    return APR_SUCCESS;
}