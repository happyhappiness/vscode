static const char *set_cookie_form_location(cmd_parms * cmd, void *config, const char *location)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->location = location;
    conf->location_set = 1;
    return check_string(cmd, location);
}