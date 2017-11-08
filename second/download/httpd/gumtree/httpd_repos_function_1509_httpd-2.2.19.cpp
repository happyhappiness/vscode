static const char * add_pass_reverse(cmd_parms *cmd, void *dconf, const char *f,
                                     const char *r, const char *i)
{
    proxy_dir_conf *conf = dconf;
    struct proxy_alias *new;
    const char *fake;
    const char *real;
    const char *interp;

    if (cmd->path == NULL) {
        fake = f;
        real = r;
        interp = i;
        if (r == NULL || !strcasecmp(r, "interpolate")) {
            return "ProxyPassReverse needs a path when not defined in a location";
        }
    }
    else {
        fake = cmd->path;
        real = f;
        if (r && strcasecmp(r, "interpolate")) {
            return "ProxyPassReverse can not have a path when defined in a location";
        }
        interp = r;
    }

    new = apr_array_push(conf->raliases);
    new->fake = fake;
    new->real = real;
    new->flags = interp ? PROXYPASS_INTERPOLATE : 0;

    return NULL;
}