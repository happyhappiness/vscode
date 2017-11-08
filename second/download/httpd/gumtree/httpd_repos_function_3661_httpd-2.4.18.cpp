static int log_header(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    if (info->r)
        return log_table_entry(info->r->headers_in, arg, buf, buflen);

    return 0;
}