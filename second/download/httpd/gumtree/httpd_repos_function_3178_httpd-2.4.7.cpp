static int log_server_name(const ap_errorlog_info *info, const char *arg,
                           char *buf, int buflen)
{
    if (info->r)
        return cpystrn(buf, ap_get_server_name((request_rec *)info->r), buflen);

    return 0;
}