static int log_apr_status(const ap_errorlog_info *info, const char *arg,
                          char *buf, int buflen)
{
    apr_status_t status = info->status;
    int len;
    if (!status)
        return 0;

    if (status < APR_OS_START_EAIERR) {
        len = apr_snprintf(buf, buflen, "(%d)", status);
    }
    else if (status < APR_OS_START_SYSERR) {
        len = apr_snprintf(buf, buflen, "(EAI %d)",
                           status - APR_OS_START_EAIERR);
    }
    else if (status < 100000 + APR_OS_START_SYSERR) {
        len = apr_snprintf(buf, buflen, "(OS %d)",
                           status - APR_OS_START_SYSERR);
    }
    else {
        len = apr_snprintf(buf, buflen, "(os 0x%08x)",
                           status - APR_OS_START_SYSERR);
    }
    apr_strerror(status, buf + len, buflen - len);
    len += strlen(buf + len);
    return len;
}