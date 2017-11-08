static int log_note(const ap_errorlog_info *info, const char *arg,
                      char *buf, int buflen)
{
    /* XXX: maybe escaping the entry is not necessary for notes? */
    if (info->r)
        return log_table_entry(info->r->notes, arg, buf, buflen);

    return 0;
}