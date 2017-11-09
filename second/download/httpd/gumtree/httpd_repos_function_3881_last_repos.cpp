static const char *authn_cache_enable(cmd_parms *cmd, void *CFG)
{
    const char *errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    configured = 1;
    return errmsg;
}