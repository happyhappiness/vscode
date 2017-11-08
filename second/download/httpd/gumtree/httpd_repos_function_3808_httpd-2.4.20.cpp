static int log_virtual_host(const ap_errorlog_info *info, const char *arg,
                            char *buf, int buflen)
{
    if (info->s)
        return cpystrn(buf, info->s->server_hostname, buflen);

    return 0;
}