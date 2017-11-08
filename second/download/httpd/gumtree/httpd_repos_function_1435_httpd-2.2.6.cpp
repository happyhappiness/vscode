static int proxy_trans(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    int i, len;
    struct proxy_alias *ent = (struct proxy_alias *) conf->aliases->elts;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    char *found = NULL;

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
        if (ent[i].regex) {
            if (!ap_regexec(ent[i].regex, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
                if ((ent[i].real[0] == '!') && (ent[i].real[1] == '\0')) {
                    return DECLINED;
                }
                found = ap_pregsub(r->pool, ent[i].real, r->uri, AP_MAX_REG_MATCH,
                                   regm);
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
                if (found && strcmp(found, ent[i].real)) {
                    found = apr_pstrcat(r->pool, "proxy:", found, NULL);
                }
                else {
                    found = apr_pstrcat(r->pool, "proxy:", ent[i].real, r->uri,
                                        NULL);
                }
            }
        }
        else {
            len = alias_match(r->uri, ent[i].fake);

            if (len > 0) {
                if ((ent[i].real[0] == '!') && (ent[i].real[1] == '\0')) {
                    return DECLINED;
                }

                found = apr_pstrcat(r->pool, "proxy:", ent[i].real,
                                    r->uri + len, NULL);
            }
        }
        if (found) {
            r->filename = found;
            r->handler = "proxy-server";
            r->proxyreq = PROXYREQ_REVERSE;
            return OK;
        }
    }
    return DECLINED;
}