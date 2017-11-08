static int log_remote_address(const ap_errorlog_info *info, const char *arg,
                              char *buf, int buflen)
{
    if (info->r && !(arg && *arg == 'c'))
        return apr_snprintf(buf, buflen, "%s:%d", info->r->useragent_ip,
                            info->r->useragent_addr->port);
    else if (info->c)
        return apr_snprintf(buf, buflen, "%s:%d", info->c->client_ip,
                            info->c->client_addr->port);
    else
        return 0;
}