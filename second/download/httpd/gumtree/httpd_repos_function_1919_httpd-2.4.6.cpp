static int xlate_name(request_rec *r)
{
    int i;
    const char *name;
    char *backend;
    apr_dbm_t *db;
    apr_status_t rv;
    apr_datum_t key, val;
    struct proxy_alias *ralias;
    proxy_dir_conf *dconf;
    express_server_conf *sconf;

    sconf = ap_get_module_config(r->server->module_config, &proxy_express_module);
    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);

    if (!sconf->enabled) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01001) "proxy_express: Enabled");
    if (!sconf->dbmfile || (r->filename && strncmp(r->filename, "proxy:", 6) == 0)) {
        /* it should be go on as an internal proxy request */
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01002)
                  "proxy_express: Opening DBM file: %s (%s)",
                  sconf->dbmfile, sconf->dbmtype);
    rv = apr_dbm_open_ex(&db, sconf->dbmtype, sconf->dbmfile, APR_DBM_READONLY,
                         APR_OS_DEFAULT, r->pool);
    if (rv != APR_SUCCESS) {
        return DECLINED;
    }

    name = ap_get_server_name(r);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01003)
                  "proxy_express: looking for %s", name);
    key.dptr = (char *)name;
    key.dsize = strlen(key.dptr);

    rv = apr_dbm_fetch(db, key, &val);
    apr_dbm_close(db);
    if (rv != APR_SUCCESS) {
        return DECLINED;
    }

    backend = apr_pstrmemdup(r->pool, val.dptr, val.dsize);
    if (!backend) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01004)
                  "proxy_express: found %s -> %s", name, backend);
    r->filename = apr_pstrcat(r->pool, "proxy:", backend, r->uri, NULL);
    r->handler = "proxy-server";
    r->proxyreq = PROXYREQ_REVERSE;

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01005)
                  "proxy_express: rewritten as: %s", r->filename);

    ralias = (struct proxy_alias *)dconf->raliases->elts;
    /*
     * See if we have already added a ProxyPassReverse entry
     * for this host... If so, don't do it again.
     */
    /*
     * NOTE: dconf is process specific so this wil only
     *       work as long as we maintain that this process
     *       or thread is handling the backend
     */
    for (i = 0; i < dconf->raliases->nelts; i++, ralias++) {
        if (strcasecmp(backend, ralias->real) == 0) {
            ralias = NULL;
            break;
        }
    }

    /* Didn't find one... add it */
    if (!ralias) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01006)
                      "proxy_express: adding PPR entry");
        ralias = apr_array_push(dconf->raliases);
        ralias->fake = "/";
        ralias->real = apr_pstrdup(dconf->raliases->pool, backend);
        ralias->flags = 0;
    }
    return OK;
}