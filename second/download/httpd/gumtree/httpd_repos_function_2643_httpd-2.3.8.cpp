static const char *set_authoritative(cmd_parms * cmd, void *config, int flag)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->authoritative = flag;
    conf->authoritative_set = 1;
    return NULL;
}