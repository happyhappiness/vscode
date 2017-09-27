                        ? proxy_interpolate(r, old[i].fake) : old[i].fake;
        newcopy->real = (old[i].flags & PROXYPASS_INTERPOLATE)
                        ? proxy_interpolate(r, old[i].real) : old[i].real;
    }
    return ret;
}

PROXY_DECLARE(int) ap_proxy_trans_match(request_rec *r, struct proxy_alias *ent,
                                        proxy_dir_conf *dconf)
{
    int len;
    const char *fake;
    const char *real;
    ap_regmatch_t regm[AP_MAX_REG_MATCH];
    ap_regmatch_t reg1[AP_MAX_REG_MATCH];
    char *found = NULL;
    int mismatch = 0;
    unsigned int nocanon = ent->flags & PROXYPASS_NOCANON;
    const char *use_uri = nocanon ? r->unparsed_uri : r->uri;

    if (dconf && (dconf->interpolate_env == 1) && (ent->flags & PROXYPASS_INTERPOLATE)) {
        fake = proxy_interpolate(r, ent->fake);
        real = proxy_interpolate(r, ent->real);
    }
    else {
        fake = ent->fake;
        real = ent->real;
    }
    if (ent->regex) {
        if (!ap_regexec(ent->regex, r->uri, AP_MAX_REG_MATCH, regm, 0)) {
            if ((real[0] == '!') && (real[1] == '\0')) {
                return DECLINED;
            }
            /* test that we haven't reduced the URI */
            if (nocanon && ap_regexec(ent->regex, r->unparsed_uri,
                    AP_MAX_REG_MATCH, reg1, 0)) {
                mismatch = 1;
                use_uri = r->uri;
            }
            found = ap_pregsub(r->pool, real, use_uri, AP_MAX_REG_MATCH,
                    (use_uri == r->uri) ? regm : reg1);
            if (!found) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01135)
                              "Substitution in regular expression failed. "
                              "Replacement too long?");
                return HTTP_INTERNAL_SERVER_ERROR;
            }

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
            if (strcmp(found, real) != 0) {
                found = apr_pstrcat(r->pool, "proxy:", found, NULL);
            }
            else {
                found = apr_pstrcat(r->pool, "proxy:", real, use_uri, NULL);
            }
        }
    }
    else {
        len = alias_match(r->uri, fake);

        if (len != 0) {
            if ((real[0] == '!') && (real[1] == '\0')) {
                return DECLINED;
            }
            if (nocanon && len != alias_match(r->unparsed_uri, ent->fake)) {
                mismatch = 1;
                use_uri = r->uri;
            }
            found = apr_pstrcat(r->pool, "proxy:", real, use_uri + len, NULL);
        }
    }
    if (mismatch) {
        /* We made a reducing transformation, so we can't safely use
         * unparsed_uri.  Safe fallback is to ignore nocanon.
         */
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01136)
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
        if (ent->flags & PROXYPASS_NOQUERY) {
            apr_table_setn(r->notes, "proxy-noquery", "1");
        }
        return OK;
    }

    return DONE;
}

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

static int proxy_walk(request_rec *r)
