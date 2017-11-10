static const char *set_cookie_form_username(cmd_parms * cmd, void *config, const char *username)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->username = username;
    conf->username_set = 1;
    return check_string(cmd, username);
}