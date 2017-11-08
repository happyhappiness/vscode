static const char *
    add_proxy_noregex(cmd_parms *cmd, void *dummy, const char *f1, const char *r1)
{
    return add_proxy(cmd, dummy, f1, r1, 0);
}