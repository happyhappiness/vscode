static void ap_authn_cache_store(request_rec *r, const char *module,
                                 const char *user, const char *realm,
                                 const char* data)
{
    apr_status_t rv;
    authn_cache_dircfg *dcfg;
    const char *key;
    apr_time_t expiry;
    int i;
    int use_cache = 0;

    /* first check whether we're cacheing for this module */
    dcfg = ap_get_module_config(r->per_dir_config, &authn_socache_module);
    if (!dcfg->providers) {
        return;
    }
    for (i = 0; i < dcfg->providers->nelts; ++i) {
        if (!strcmp(module, APR_ARRAY_IDX(dcfg->providers, i, const char*))) {
            use_cache = 1;
            break;
        }
    }
    if (!use_cache) {
        return;
    }

    /* OK, we're on.  Grab mutex to do our business */
    rv = apr_global_mutex_trylock(authn_cache_mutex);
    if (APR_STATUS_IS_EBUSY(rv)) {
        /* don't wait around; just abandon it */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                      "authn credentials for %s not cached (mutex busy)", user);
        return;
    }
    else if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Failed to cache authn credentials for %s in %s",
                      module, dcfg->context);
        return;
    }

    /* We have the mutex, so go ahead */
    /* first build our key and determine expiry time */
    key = construct_key(r, dcfg->context, user, realm);
    expiry = apr_time_now() + dcfg->timeout;

    /* store it */
    rv = socache_provider->store(socache_instance, r->server,
                                 (unsigned char*)key, strlen(key), expiry,
                                 (unsigned char*)data, strlen(data), r->pool);
    if (rv == APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Cached authn credentials for %s in %s",
                      user, dcfg->context);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Failed to cache authn credentials for %s in %s",
                      module, dcfg->context);
    }

    /* We're done with the mutex */
    rv = apr_global_mutex_unlock(authn_cache_mutex);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, "Failed to release mutex!");
    }
    return;
}