
static const char *add_env_module_vars_set(cmd_parms *cmd, void *sconf_,
                                           const char *name, const char *value)
{
    env_dir_config_rec *sconf = sconf_;

    if (ap_strchr_c(name, '=')) {
        char *env, *plast;

        env = apr_strtok(apr_pstrdup(cmd->temp_pool, name), "=", &plast);

        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(10032)
                     "Spurious usage of '=' in an environment variable name. "
                     "'%s %s %s' expected instead?", cmd->cmd->name, env, plast);
    
    }

    /* name is mandatory, value is optional.  no value means
     * set the variable to an empty string
     */
    apr_table_setn(sconf->vars, name, value ? value : "");

    return NULL;
