static int proxy_fixup(request_rec *r)
{
    char *url, *p;
    int access_status;
    proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                 &proxy_module);

    if (!r->proxyreq || !r->filename || strncmp(r->filename, "proxy:", 6) != 0)
        return DECLINED;

    /* XXX: Shouldn't we try this before we run the proxy_walk? */
    url = &r->filename[6];

    if ((dconf->interpolate_env == 1) && (r->proxyreq == PROXYREQ_REVERSE)) {
        /* create per-request copy of reverse proxy conf,
         * and interpolate vars in it
         */
        proxy_req_conf *rconf = apr_palloc(r->pool, sizeof(proxy_req_conf));
        ap_set_module_config(r->request_config, &proxy_module, rconf);
        rconf->raliases = proxy_vars(r, dconf->raliases);
        rconf->cookie_paths = proxy_vars(r, dconf->cookie_paths);
        rconf->cookie_domains = proxy_vars(r, dconf->cookie_domains);
    }

    /* canonicalise each specific scheme */
    if ((access_status = proxy_run_canon_handler(r, url))) {
        return access_status;
    }

    p = strchr(url, ':');
    if (p == NULL || p == url)
        return HTTP_BAD_REQUEST;

    return OK;      /* otherwise; we've done the best we can */
}