static const char *set_cookie_name(cmd_parms *cmd, void *mconfig,
                                   const char *name)
{
    cookie_dir_rec *dcfg = (cookie_dir_rec *) mconfig;

    dcfg->cookie_name = apr_pstrdup(cmd->pool, name);

    set_and_comp_regexp(dcfg, cmd->pool, name);

    if (dcfg->regexp == NULL) {
        return "Regular expression could not be compiled.";
    }
    if (dcfg->regexp->re_nsub + 1 != NUM_SUBS) {
        return apr_pstrcat(cmd->pool, "Invalid cookie name \"",
                           name, "\"", NULL);
    }

    return NULL;
}