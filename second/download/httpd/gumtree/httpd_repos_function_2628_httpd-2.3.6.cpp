static const char *set_login_required_location(cmd_parms * cmd, void *config, const char *loginrequired)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->loginrequired = loginrequired;
    conf->loginrequired_set = 1;
    return NULL;
}