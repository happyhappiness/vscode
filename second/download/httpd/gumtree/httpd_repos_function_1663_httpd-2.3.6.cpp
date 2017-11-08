static const char *add_pass(cmd_parms *cmd, void *vconf,
                            int argc, char *const argv[])
{
    int i;
    apr_status_t rv;
    serf_config_t *conf = (serf_config_t *) vconf;

    if (argc < 1) {
        return "SerfPass must have at least a URI.";
    }

    rv = apr_uri_parse(cmd->pool, argv[0], &conf->url);

    if (rv != APR_SUCCESS) {
        return "mod_serf: Unable to parse SerfPass url.";
    }

    if (!conf->url.scheme) {
        return "mod_serf: Need scheme part in url.";
    }

    /* XXXX: These are bugs in apr_uri_parse. Fixme. */
    if (!conf->url.port) {
        conf->url.port = apr_uri_port_of_scheme(conf->url.scheme);
    }

    if (!conf->url.path) {
        conf->url.path = "/";
    }

    for (i = 1; i < argc; i++) {
        const char *p = argv[i];
        const char *x = ap_strchr_c(p, '=');
        
        if (x) {
            char *key = apr_pstrndup(cmd->pool, p, x-p);
            if (strcmp(key, "preservehost") == 0) {
                conf->preservehost = is_true(x+1);
            }
        }
    }

    conf->on = 1;
    
    return NULL;
}