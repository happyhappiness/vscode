static const char *set_logout_location(cmd_parms * cmd, void *config, const char *logout)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    const char *err;

    conf->logout = ap_expr_parse_cmd(cmd, logout, AP_EXPR_FLAG_STRING_RESULT,
                                        &err, NULL);
    if (err) {
        return apr_psprintf(cmd->pool,
                            "Could not parse logout required expression '%s': %s",
                            logout, err);
    }
    conf->logout_set = 1;

    return NULL;
}