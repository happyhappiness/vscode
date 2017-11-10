static const char *set_fake_basic_auth(cmd_parms * cmd, void *config, int flag)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->fakebasicauth = flag;
    conf->fakebasicauth_set = 1;
    return NULL;
}