static const char *set_cookie_name(cmd_parms *cmd, void *mconfig,
                                   const char *name)
{
    cookie_dir_rec *dcfg = (cookie_dir_rec *) mconfig;

    dcfg->cookie_name = apr_pstrdup(cmd->pool, name);
    return NULL;
}