static const char *set_cookie_form_mimetype(cmd_parms * cmd, void *config, const char *mimetype)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->mimetype = mimetype;
    conf->mimetype_set = 1;
    return check_string(cmd, mimetype);
}