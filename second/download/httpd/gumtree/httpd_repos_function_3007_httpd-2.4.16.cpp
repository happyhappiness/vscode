static const char *set_cookie_form_password(cmd_parms * cmd, void *config, const char *password)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->password = password;
    conf->password_set = 1;
    return check_string(cmd, password);
}