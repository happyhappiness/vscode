static const char *set_login_success_location(cmd_parms * cmd, void *config, const char *loginsuccess)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->loginsuccess = loginsuccess;
    conf->loginsuccess_set = 1;
    return NULL;
}