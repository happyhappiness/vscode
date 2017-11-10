static const char* cookie_domain(cmd_parms *cmd, void *dconf, const char *f,
                                 const char *r, const char *interp)
{
    proxy_dir_conf *conf = dconf;
    struct proxy_alias *new;

    new = apr_array_push(conf->cookie_domains);
    new->fake = f;
    new->real = r;
    new->flags = interp ? PROXYPASS_INTERPOLATE : 0;
    return NULL;
}