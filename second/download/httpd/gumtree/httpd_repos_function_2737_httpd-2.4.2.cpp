static const char *set_disable_no_store(cmd_parms * cmd, void *config, int flag)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->disable_no_store = flag;
    conf->disable_no_store_set = 1;
    return NULL;
}