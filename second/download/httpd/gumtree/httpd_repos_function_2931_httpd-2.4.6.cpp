static void *create_auth_form_dir_config(apr_pool_t * p, char *d)
{
    auth_form_config_rec *conf = apr_pcalloc(p, sizeof(*conf));

    conf->dir = d;
    /* Any failures are fatal. */
    conf->authoritative = 1;

    /* form size defaults to 8k */
    conf->form_size = HUGE_STRING_LEN;

    /* default form field names */
    conf->username = "httpd_username";
    conf->password = "httpd_password";
    conf->location = "httpd_location";
    conf->method = "httpd_method";
    conf->mimetype = "httpd_mimetype";
    conf->body = "httpd_body";

    return conf;
}