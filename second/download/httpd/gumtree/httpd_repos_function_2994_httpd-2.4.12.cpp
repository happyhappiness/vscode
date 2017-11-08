static const char *set_login_success_location(cmd_parms * cmd, void *config, const char *loginsuccess)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    const char *err;

    conf->loginsuccess = ap_expr_parse_cmd(cmd, loginsuccess, AP_EXPR_FLAG_STRING_RESULT,
                                        &err, NULL);
    if (err) {
        return apr_psprintf(cmd->pool,
                            "Could not parse login success expression '%s': %s",
                            loginsuccess, err);
    }
    conf->loginsuccess_set = 1;

    return NULL;
}