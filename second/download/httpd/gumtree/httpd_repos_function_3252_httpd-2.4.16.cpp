static int log_env_var(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    if (info->r)
        return log_table_entry(info->r->subprocess_env, arg, buf, buflen);

    return 0;
}