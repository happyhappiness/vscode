static int proxy_trans(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    int i, len;
    struct proxy_alias *ent = (struct proxy_alias *) conf->aliases->elts;
    proxy_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
                                                 &proxy_module);
    const char *fake;
    const char *real;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    ap_regmatch_t reg1[AP_MAX_REG_MATCH];
    char *found = NULL;
    int mismatch = 0;

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
        unsigned int nocanon = ent[i].flags & PROXYPASS_NOCANON;
        const char *use_uri = nocanon ? r->unparsed_uri : r->uri;
        if ((dconf->interpolate_env == 1)
            && (ent[i].flags & PROXYPASS_INTERPOLATE)) {
            fake = proxy_interpolate(r, ent[i].fake);
            real = proxy_interpolate(r, ent[i].real);
        }
        else {
            fake = ent[i].fake;
            real = ent[i].real;
        }
        if (ent[i].regex) {
            if (!ap_regexec(ent[i].regex, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
                if ((real[0] == '!') && (real[1] == '\0')) {
                    return DECLINED;
                }
                /* test that we haven't reduced the URI */
                if (nocanon && ap_regexec(ent[i].regex, r->unparsed_uri,
                                          AP_MAX_REG_MATCH, reg1, 0)) {
                    mismatch = 1;
                    use_uri = r->uri;
                }
                found = ap_pregsub(r->pool, real, use_uri, AP_MAX_REG_MATCH,
                                   (use_uri == r->uri) ? regm : reg1);
                /* Note: The strcmp() below catches cases where there
                 * was no regex substitution. This is so cases like:
                 *
                 *    ProxyPassMatch \.gif balancer://foo
                 *
                 * will work "as expected". The upshot is that the 2
                 * directives below act the exact same way (ie: $1 is implied):
                 *
                 *    ProxyPassMatch ^(/.*\.gif)$ balancer://foo
                 *    ProxyPassMatch ^(/.*\.gif)$ balancer://foo$1
                 *
                 * which may be confusing.
                 */
                if (found && strcmp(found, real)) {
                    found = apr_pstrcat(r->pool, "proxy:", found, NULL);
                }
                else {
                    found = apr_pstrcat(r->pool, "proxy:", real,
                                        use_uri, NULL);
                }
            }
        }
        else {
            len = alias_match(r->uri, fake);

            if (len != 0) {
                if ((real[0] == '!') && (real[1] == '\0')) {
                    return DECLINED;
                }
                if (nocanon
                    && len != alias_match(r->unparsed_uri, ent[i].fake)) {
                    mismatch = 1;
                    use_uri = r->uri;
                }
                found = apr_pstrcat(r->pool, "proxy:", real,
                                    use_uri + len, NULL);
            }
        }
        if (mismatch) {
            /* We made a reducing transformation, so we can't safely use
             * unparsed_uri.  Safe fallback is to ignore nocanon.
             */
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "Unescaped URL path matched ProxyPass; ignoring unsafe nocanon");
        }

        if (found) {
            r->filename = found;
            r->handler = "proxy-server";
            r->proxyreq = PROXYREQ_REVERSE;
            if (nocanon && !mismatch) {
                /* mod_proxy_http needs to be told.  Different module. */
                apr_table_setn(r->notes, "proxy-nocanon", "1");
            }
            return OK;
        }
    }
    return DECLINED;
}