static const char *set_cookie_log(cmd_parms *cmd, void *dummy, const char *fn)
{
    return add_custom_log(cmd, dummy, fn, "%{Cookie}n \"%r\" %t", NULL);
}