static int log_module_name(const ap_errorlog_info *info, const char *arg,
                           char *buf, int buflen)
{
    return cpystrn(buf, ap_find_module_short_name(info->module_index), buflen);
}