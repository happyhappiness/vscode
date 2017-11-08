static const char *set_logout_location(cmd_parms * cmd, void *config, const char *logout)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->logout = logout;
    conf->logout_set = 1;
    return NULL;
}