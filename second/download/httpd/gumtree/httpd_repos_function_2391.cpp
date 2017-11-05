static const char *noloris_recheck(cmd_parms *cmd, void *cfg, const char *val)
{
    const char* err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (!err) {
        recheck_time = apr_time_from_sec(atoi(val));
    }
    return err;
}