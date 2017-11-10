static const char *header_cmd(cmd_parms *cmd, void *indirconf,
                              const char *args)
{
    const char *s;
    const char *action;
    const char *hdr;
    const char *val;
    const char *envclause;

    s = apr_pstrdup(cmd->pool, args);
    action = ap_getword_conf(cmd->pool, &s);
    if (cmd->info == &hdr_out) {
        if (!strcasecmp(action, "always")) {
            cmd->info = &hdr_err;
            action = ap_getword_conf(cmd->pool, &s);
        }
        else if (!strcasecmp(action, "onsuccess")) {
            action = ap_getword_conf(cmd->pool, &s);
        }
    }
    hdr = ap_getword_conf(cmd->pool, &s);
    val = *s ? ap_getword_conf(cmd->pool, &s) : NULL;
    envclause = *s ? ap_getword_conf(cmd->pool, &s) : NULL;

    if (*s) {
        return apr_pstrcat(cmd->pool, cmd->cmd->name,
                           " has too many arguments", NULL);
    }

    return header_inout_cmd(cmd, indirconf, action, hdr, val, envclause);
}