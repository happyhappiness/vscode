static const char *
    set_proxy_exclude(cmd_parms *parms, void *dummy, const char *arg)
{
    server_rec *s = parms->server;
    proxy_server_conf *conf =
    ap_get_module_config(s->module_config, &proxy_module);
    struct noproxy_entry *new;
    struct noproxy_entry *list = (struct noproxy_entry *) conf->noproxies->elts;
    struct apr_sockaddr_t *addr;
    int found = 0;
    int i;

    /* Don't duplicate entries */
    for (i = 0; i < conf->noproxies->nelts; i++) {
        if (strcasecmp(arg, list[i].name) == 0) { /* ignore case for host names */
            found = 1;
        }
    }

    if (!found) {
        new = apr_array_push(conf->noproxies);
        new->name = arg;
        if (APR_SUCCESS == apr_sockaddr_info_get(&addr, new->name, APR_UNSPEC, 0, 0, parms->pool)) {
            new->addr = addr;
        }
        else {
            new->addr = NULL;
        }
    }
    return NULL;
}