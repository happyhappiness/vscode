static const char*
    cookie_domain(cmd_parms *cmd, void *dconf, const char *f, const char *r)
{
    proxy_dir_conf *conf = dconf;
    struct proxy_alias *new;

    new = apr_array_push(conf->cookie_domains);
    new->fake = f;
    new->real = r;

    return NULL;
}