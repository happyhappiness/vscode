static const char* 
unixd_set_group(cmd_parms *cmd, void *dummy,
                                         const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err != NULL) {
        return err;
    }

    ap_unixd_config.group_id = ap_gname2id(arg);

    return NULL;
}