const char *ssl_cmd_SSLRequire(cmd_parms *cmd,
                               void *dcfg,
                               const char *arg)
{
    SSLDirConfigRec *dc = (SSLDirConfigRec *)dcfg;
    ap_expr_info_t *info = apr_pcalloc(cmd->pool, sizeof(ap_expr_info_t));
    ssl_require_t *require;
    const char *errstring;

    info->flags = AP_EXPR_FLAG_SSL_EXPR_COMPAT;
    info->filename = cmd->directive->filename;
    info->line_number = cmd->directive->line_num;
    info->module_index = APLOG_MODULE_INDEX;
    errstring = ap_expr_parse(cmd->pool, cmd->temp_pool, info, arg, NULL);
    if (errstring) {
        return apr_pstrcat(cmd->pool, "SSLRequire: ", errstring, NULL);
    }

    require = apr_array_push(dc->aRequirement);
    require->cpExpr = apr_pstrdup(cmd->pool, arg);
    require->mpExpr = info;

    return NULL;
}