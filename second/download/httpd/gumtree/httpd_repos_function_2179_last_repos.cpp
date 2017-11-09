static const char *cmd_setenv(cmd_parms *cmd, void *in_dconf,
                              const char *arg1, const char *arg2,
                              const char *arg3)
{
    fcgi_dirconf_t *dconf = in_dconf;
    const char *err;
    sei_entry *new;
    const char *envvar = arg2;

    new = apr_array_push(dconf->env_fixups);
    new->cond = ap_expr_parse_cmd(cmd, arg1, 0, &err, NULL);
    if (err) {
        return apr_psprintf(cmd->pool, "Could not parse expression \"%s\": %s",
                            arg1, err);
    }

    if (envvar[0] == '!') {
        /* Unset mode. */
        if (arg3) {
            return apr_psprintf(cmd->pool, "Third argument (\"%s\") is not "
                                "allowed when using ProxyFCGISetEnvIf's unset "
                                "mode (%s)", arg3, envvar);
        }
        else if (!envvar[1]) {
            /* i.e. someone tried to give us a name of just "!" */
            return "ProxyFCGISetEnvIf: \"!\" is not a valid variable name";
        }

        new->subst = NULL;
    }
    else {
        /* Set mode. */
        if (!arg3) {
            /* A missing expr-value should be treated as empty. */
            arg3 = "";
        }

        new->subst = ap_expr_parse_cmd(cmd, arg3, AP_EXPR_FLAG_STRING_RESULT, &err, NULL);
        if (err) {
            return apr_psprintf(cmd->pool, "Could not parse expression \"%s\": %s",
                                arg3, err);
        }
    }

    new->envname = envvar;

    return NULL;
}