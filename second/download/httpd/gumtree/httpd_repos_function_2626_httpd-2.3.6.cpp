static const char *set_cookie_form_body(cmd_parms * cmd, void *config, const char *body)
{
    auth_form_config_rec *conf = (auth_form_config_rec *) config;
    conf->body = body;
    conf->body_set = 1;
    return check_string(cmd, body);
}