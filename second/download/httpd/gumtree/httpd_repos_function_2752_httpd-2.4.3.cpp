static const char *set_site_passphrase(cmd_parms * cmd, void *config, const char *site)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->site = site;
    conf->site_set = 1;
    return NULL;
}