static int log_local_address(const ap_errorlog_info *info, const char *arg,
                             char *buf, int buflen)
{
    if (info->c)
        return apr_snprintf(buf, buflen, "%s:%d", info->c->local_ip,
                            info->c->local_addr->port);
    else
        return 0;
}