static int proxy_trans(request_rec *r)
{
    int i;
    struct proxy_alias *ent;
    proxy_dir_conf *dconf;
    proxy_server_conf *conf;

    if (r->proxyreq) {
        /* someone has already set up the proxy, it was possibly ourselves
         * in proxy_detect
         */
        return OK;
    }

    if ((r->unparsed_uri[0] == '*' && r->unparsed_uri[1] == '\0')
        || !r->uri || r->uri[0] != '/') {
        return DECLINED;
    }

    /* XXX: since r->uri has been manipulated already we're not really
     * compliant with RFC1945 at this point.  But this probably isn't
     * an issue because this is a hybrid proxy/origin server.
     */

    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);

    /* short way - this location is reverse proxied? */
    if (dconf->alias) {
        int rv = ap_proxy_trans_match(r, dconf->alias, dconf);
        if (DONE != rv) {
            return rv;
        }
    }

    conf = (proxy_server_conf *) ap_get_module_config(r->server->module_config,
                                                      &proxy_module);

    /* long way - walk the list of aliases, find a match */
    if (conf->aliases->nelts) {
        ent = (struct proxy_alias *) conf->aliases->elts;
        for (i = 0; i < conf->aliases->nelts; i++) {
            int rv = ap_proxy_trans_match(r, &ent[i], dconf);
            if (DONE != rv) {
                return rv;
            }
        }
    }
    return DECLINED;
}