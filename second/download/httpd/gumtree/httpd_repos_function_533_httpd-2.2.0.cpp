static const char *add_setenvif(cmd_parms *cmd, void *mconfig,
                                const char *args)
{
    char *fname;

    /* get header name */
    fname = ap_getword_conf(cmd->pool, &args);
    if (!*fname) {
        return apr_pstrcat(cmd->pool, "Missing header-field name for ",
                           cmd->cmd->name, NULL);
    }
    return add_setenvif_core(cmd, mconfig, fname, args);
}