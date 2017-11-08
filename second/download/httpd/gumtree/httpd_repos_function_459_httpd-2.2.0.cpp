static const char *add_env_module_vars_passed(cmd_parms *cmd, void *sconf_,
                                              const char *arg)
{
    env_dir_config_rec *sconf = sconf_;
    apr_table_t *vars = sconf->vars;
    const char *env_var;

    env_var = getenv(arg);
    if (env_var != NULL) {
        apr_table_setn(vars, arg, apr_pstrdup(cmd->pool, env_var));
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "PassEnv variable %s was undefined", arg);
    }

    return NULL;
}