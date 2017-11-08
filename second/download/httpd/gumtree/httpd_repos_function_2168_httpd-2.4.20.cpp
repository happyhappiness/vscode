static const char *scgi_set_internal_redirect(cmd_parms *cmd, void *mconfig,
                                              const char *arg)
{
    scgi_config *conf = mconfig;

    if (!strcasecmp(arg, "Off")) {
        conf->internal_redirect = scgi_internal_redirect_off;
    }
    else if (!strcasecmp(arg, "On")) {
        conf->internal_redirect = scgi_internal_redirect_on;
    }
    else {
        conf->internal_redirect = arg;
    }
    return NULL;
}