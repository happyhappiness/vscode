static int log_ctime(const ap_errorlog_info *info, const char *arg,
                     char *buf, int buflen)
{
    int time_len = buflen;
    int option = AP_CTIME_OPTION_NONE;

    while (arg && *arg) {
        switch (*arg) {
            case 'u':   option |= AP_CTIME_OPTION_USEC;
                        break;
            case 'c':   option |= AP_CTIME_OPTION_COMPACT;
                        break;
        }
        arg++;
    }

    ap_recent_ctime_ex(buf, apr_time_now(), option, &time_len);

    /* ap_recent_ctime_ex includes the trailing \0 in time_len */
    return time_len - 1;
}