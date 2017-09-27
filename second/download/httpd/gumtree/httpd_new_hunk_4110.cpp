    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01003)
                  "proxy_express: looking for %s", name);
    key.dptr = (char *)name;
    key.dsize = strlen(key.dptr);

    rv = apr_dbm_fetch(db, key, &val);
    if (rv == APR_SUCCESS) {
        backend = apr_pstrmemdup(r->pool, val.dptr, val.dsize);
    }
    apr_dbm_close(db);
    if (rv != APR_SUCCESS || !backend) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01004)
                  "proxy_express: found %s -> %s", name, backend);
    r->filename = apr_pstrcat(r->pool, "proxy:", backend, r->uri, NULL);
