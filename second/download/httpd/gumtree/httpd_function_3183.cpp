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
    if (!dcfg->providers) {
        return AUTH_USER_NOT_FOUND;
    }
    key = construct_key(r, dcfg->context, user, NULL);
    rv = socache_provider->retrieve(socache_instance, r->server,
                                    (unsigned char*)key, strlen(key),
                                    val, &vallen, r->pool);

    if (APR_STATUS_IS_NOTFOUND(rv)) {
        /* not found - just return */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Authn cache: no credentials found for %s", user);
        return AUTH_USER_NOT_FOUND;
    }
    else if (rv == APR_SUCCESS) {
        /* OK, we got a value */
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Authn cache: found credentials for %s", user);
        val[vallen] = 0;
    }
    else {
        /* error: give up and pass the buck */
        /* FIXME: getting this for NOTFOUND - prolly a bug in mod_socache */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "Error accessing authentication cache");
        return AUTH_USER_NOT_FOUND;
    }

    rv = apr_password_validate(password, (char*) val);
    if (rv != APR_SUCCESS) {
        return AUTH_DENIED;
    }

    return AUTH_GRANTED;
}