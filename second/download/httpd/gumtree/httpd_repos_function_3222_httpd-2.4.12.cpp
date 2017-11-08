static int log_loglevel(const ap_errorlog_info *info, const char *arg,
                        char *buf, int buflen)
{
    if (info->level < 0)
        return 0;
    else
        return cpystrn(buf, priorities[info->level].t_name, buflen);
}