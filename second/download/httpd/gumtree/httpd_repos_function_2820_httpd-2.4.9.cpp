static const char *add_basic_fake(cmd_parms * cmd, void *config,
        const char *user, const char *pass)
{
    auth_basic_config_rec *conf = (auth_basic_config_rec *) config;
    const char *err;

    if (!strcasecmp(user, "off")) {

        conf->fakeuser = NULL;
        conf->fakepass = NULL;
        conf->fake_set = 1;

    }
    else {

        /* if password is unspecified, set it to the fixed string "password" to
         * be compatible with the behaviour of mod_ssl.
         */
        if (!pass) {
            pass = "password";
        }

        conf->fakeuser =
                ap_expr_parse_cmd(cmd, user, AP_EXPR_FLAG_STRING_RESULT,
                        &err, NULL);
        if (err) {
            return apr_psprintf(cmd->pool,
                    "Could not parse fake username expression '%s': %s", user,
                    err);
        }
        conf->fakepass =
                ap_expr_parse_cmd(cmd, pass, AP_EXPR_FLAG_STRING_RESULT,
                        &err, NULL);
        if (err) {
            return apr_psprintf(cmd->pool,
                    "Could not parse fake password expression '%s': %s", user,
                    err);
        }
        conf->fake_set = 1;

    }

    return NULL;
}