static const char *add_env_module_vars_unset(cmd_parms *cmd, void *sconf_,
                                             const char *arg)
{
    env_dir_config_rec *sconf = sconf_;

    /* Always UnsetEnv FOO in the same context as {Set,Pass}Env FOO
     * only if this UnsetEnv follows the {Set,Pass}Env.  The merge
     * will only apply unsetenv to the parent env (main server).
     */
    apr_table_set(sconf->unsetenv, arg, NULL);
    apr_table_unset(sconf->vars, arg);

    return NULL;
}