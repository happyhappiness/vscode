static void *proxy_html_merge(apr_pool_t *pool, void *BASE, void *ADD)
{
    proxy_html_conf *base = (proxy_html_conf *) BASE;
    proxy_html_conf *add = (proxy_html_conf *) ADD;
    proxy_html_conf *conf = apr_palloc(pool, sizeof(proxy_html_conf));

    /* don't merge declarations - just use the most specific */
    conf->links = (add->links == NULL) ? base->links : add->links;
    conf->events = (add->events == NULL) ? base->events : add->events;

    conf->charset_out = (add->charset_out == NULL)
                        ? base->charset_out : add->charset_out;

    if (add->map && base->map) {
        urlmap *a;
        conf->map = NULL;
        for (a = base->map; a; a = a->next) {
            urlmap *save = conf->map;
            conf->map = apr_pmemdup(pool, a, sizeof(urlmap));
            conf->map->next = save;
        }
        for (a = add->map; a; a = a->next) {
            urlmap *save = conf->map;
            conf->map = apr_pmemdup(pool, a, sizeof(urlmap));
            conf->map->next = save;
        }
    }
    else
        conf->map = add->map ? add->map : base->map;

    conf->doctype = (add->doctype == DEFAULT_DOCTYPE)
                    ? base->doctype : add->doctype;
    conf->etag = (add->etag == DEFAULT_ETAG) ? base->etag : add->etag;
    conf->bufsz = add->bufsz;
    if (add->flags & NORM_RESET) {
        conf->flags = add->flags ^ NORM_RESET;
        conf->metafix = add->metafix;
        conf->extfix = add->extfix;
        conf->interp = add->interp;
        conf->strip_comments = add->strip_comments;
        conf->enabled = add->enabled;
    }
    else {
        conf->flags = base->flags | add->flags;
        conf->metafix = base->metafix | add->metafix;
        conf->extfix = base->extfix | add->extfix;
        conf->interp = base->interp | add->interp;
        conf->strip_comments = base->strip_comments | add->strip_comments;
        conf->enabled = add->enabled | base->enabled;
    }
    return conf;
}