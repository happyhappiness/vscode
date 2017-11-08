static const char *set_hc_condition(cmd_parms *cmd, void *dummy, const char *arg)
{
    char *name = NULL;
    char *expr;
    sctx_t *ctx;
    hc_condition_t *cond;

    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;
    ctx = (sctx_t *) ap_get_module_config(cmd->server->module_config,
                                          &proxy_hcheck_module);

    name = ap_getword_conf(cmd->pool, &arg);
    if (!*name) {
        return apr_pstrcat(cmd->temp_pool, "Missing expression name for ",
                           cmd->cmd->name, NULL);
    }
    if (strlen(name) > (PROXY_WORKER_MAX_SCHEME_SIZE - 1)) {
        return apr_psprintf(cmd->temp_pool, "Expression name limited to %d characters",
                           (PROXY_WORKER_MAX_SCHEME_SIZE - 1));
    }
    /* get expr. Allow fancy new {...} quoting style */
    expr = ap_getword_conf2(cmd->temp_pool, &arg);
    if (!*expr) {
        return apr_pstrcat(cmd->temp_pool, "Missing expression for ",
                           cmd->cmd->name, NULL);
    }
    cond = apr_palloc(cmd->pool, sizeof(hc_condition_t));
    cond->pexpr = ap_expr_parse_cmd(cmd, expr, 0, &err, NULL);
    if (err) {
        return apr_psprintf(cmd->temp_pool, "Could not parse expression \"%s\": %s",
                            expr, err);
    }
    cond->expr = apr_pstrdup(cmd->pool, expr);
    apr_table_setn(ctx->conditions, name, (void *)cond);
    expr = ap_getword_conf(cmd->temp_pool, &arg);
    if (*expr) {
        return "error: extra parameter(s)";
    }

    return NULL;
}