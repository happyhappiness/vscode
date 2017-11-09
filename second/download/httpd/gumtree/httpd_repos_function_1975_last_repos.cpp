static const char *set_hc_tpsize (cmd_parms *cmd, void *dummy, const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err)
        return err;

    tpsize = atoi(arg);
    if (tpsize < 0)
        return "Invalid ProxyHCTPsize parameter. Parameter must be "
               ">= 0";
    return NULL;
}