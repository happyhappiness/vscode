static int proxy_trans(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    int i, len;
    struct proxy_alias *ent = (struct proxy_alias *) conf->aliases->elts;

    if (r->proxyreq) {
        /* someone has already set up the proxy, it was possibly ourselves
         * in proxy_detect
         */
        return OK;
    }

    /* XXX: since r->uri has been manipulated already we're not really
     * compliant with RFC1945 at this point.  But this probably isn't
     * an issue because this is a hybrid proxy/origin server.
     */

    for (i = 0; i < conf->aliases->nelts; i++) {
        len = alias_match(r->uri, ent[i].fake);

       if (len > 0) {
           if ((ent[i].real[0] == '!' ) && ( ent[i].real[1] == 0 )) {
               return DECLINED;
           }

           r->filename = apr_pstrcat(r->pool, "proxy:", ent[i].real,
                                 (r->uri + len ), NULL);
           r->handler = "proxy-server";
           r->proxyreq = PROXYREQ_REVERSE;
           return OK;
       }
    }
    return DECLINED;
}