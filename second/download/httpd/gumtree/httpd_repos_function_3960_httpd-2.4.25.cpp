static int log_keepalives(const ap_errorlog_info *info, const char *arg,
                          char *buf, int buflen)
{
    if (!info->c)
        return 0;

    return apr_snprintf(buf, buflen, "%d", info->c->keepalives);
}