static const char *set_login_required_location(cmd_parms * cmd, void *config, const char *loginrequired)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    const char *err;

    conf->loginrequired = ap_expr_parse_cmd(cmd, loginrequired, AP_EXPR_FLAG_STRING_RESULT,
                                        &err, NULL);
    if (err) {
        return apr_psprintf(cmd->pool,
                            "Could not parse login required expression '%s': %s",
                            loginrequired, err);
    }
    conf->loginrequired_set = 1;

    return NULL;
}