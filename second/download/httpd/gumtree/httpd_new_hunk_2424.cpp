
    /* store it */
    rv = socache_provider->store(socache_instance, r->server,
                                 (unsigned char*)key, strlen(key), expiry,
                                 (unsigned char*)data, strlen(data), r->pool);
    if (rv == APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01681)
                      "Cached authn credentials for %s in %s",
                      user, dcfg->context);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01682)
                      "Failed to cache authn credentials for %s in %s",
                      module, dcfg->context);
    }

    /* We're done with the mutex */
    rv = apr_global_mutex_unlock(authn_cache_mutex);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01683) "Failed to release mutex!");
    }
    return;
}

#define MAX_VAL_LEN 100
static authn_status check_password(request_rec *r, const char *user,
                                   const char *password)
{

    /* construct key
     * look it up
     * if found, test password
     *
     * mutexing here would be a big performance drag.
     * It's definitely unnecessary with some backends (like ndbm or gdbm)
     * Is there a risk in the general case?  I guess the only risk we
     * care about is a race condition that gets us a dangling pointer
     * to no-longer-defined memory.  Hmmm ...
     */
    apr_status_t rv;
    const char *key;
    authn_cache_dircfg *dcfg;
    unsigned char val[MAX_VAL_LEN];
    unsigned int vallen = MAX_VAL_LEN - 1;
    dcfg = ap_get_module_config(r->per_dir_config, &authn_socache_module);
    if (!configured || !dcfg->providers) {
        return AUTH_USER_NOT_FOUND;
    }
    key = construct_key(r, dcfg->context, user, NULL);
    rv = socache_provider->retrieve(socache_instance, r->server,
                                    (unsigned char*)key, strlen(key),
                                    val, &vallen, r->pool);

    if (APR_STATUS_IS_NOTFOUND(rv)) {
        /* not found - just return */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01684)
                      "Authn cache: no credentials found for %s", user);
        return AUTH_USER_NOT_FOUND;
    }
    else if (rv == APR_SUCCESS) {
        /* OK, we got a value */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01685)
                      "Authn cache: found credentials for %s", user);
        val[vallen] = 0;
    }
    else {
        /* error: give up and pass the buck */
        /* FIXME: getting this for NOTFOUND - prolly a bug in mod_socache */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01686)
                      "Error accessing authentication cache");
        return AUTH_USER_NOT_FOUND;
    }

    rv = apr_password_validate(password, (char*) val);
    if (rv != APR_SUCCESS) {
