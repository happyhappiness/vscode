static const char *set_cookie_form_method(cmd_parms * cmd, void *config, const char *method)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->method = method;
    conf->method_set = 1;
    return check_string(cmd, method);
}