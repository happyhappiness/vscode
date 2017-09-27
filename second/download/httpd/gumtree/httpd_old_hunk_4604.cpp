
static const char *add_env_module_vars_set(cmd_parms *cmd, void *sconf_,
                                           const char *name, const char *value)
{
    env_dir_config_rec *sconf = sconf_;

    /* name is mandatory, value is optional.  no value means
     * set the variable to an empty string
     */
    apr_table_setn(sconf->vars, name, value ? value : "");

    return NULL;
