    apr_table_add(t, key, value + offset);
}

PROXY_DECLARE(const char *) ap_proxy_location_reverse_map(request_rec *r,
                              proxy_dir_conf *conf, const char *url)
{
    struct proxy_alias *ent;
    int i, l1, l2;
    char *u;

    /*
     * XXX FIXME: Make sure this handled the ambiguous case of the :<PORT>
     * after the hostname
     */

    l1 = strlen(url);
    ent = (struct proxy_alias *)conf->raliases->elts;
    for (i = 0; i < conf->raliases->nelts; i++) {
        l2 = strlen(ent[i].real);
        if (l1 >= l2 && strncasecmp(ent[i].real, url, l2) == 0) {
            u = apr_pstrcat(r->pool, ent[i].fake, &url[l2], NULL);
            return ap_construct_url(r->pool, u, r);
        }
    }

    return url;
