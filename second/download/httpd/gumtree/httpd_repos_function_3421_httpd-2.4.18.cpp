static const char *set_cookie_form_size(cmd_parms * cmd, void *config,
                                             const char *arg)
{
    auth_form_config_rec *conf = config;
    apr_off_t size;

    if (APR_SUCCESS != apr_strtoff(&size, arg, NULL, 10)
        || size < 0 || size > APR_SIZE_MAX) {
        return "AuthCookieFormSize must be a size in bytes, or zero.";
    }
    conf->form_size = (apr_size_t)size;
    conf->form_size_set = 1;

    return NULL;
}