    apr_set_os_error(0);

    /* Run GetExtensionVersion() */
    if (!(isa->GetExtensionVersion)(isa->isapi_version)) {
        apr_status_t rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: failed call to GetExtensionVersion() in %s",
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

    apr_pool_cleanup_register(p, isa, cleanup_isapi,
                              apr_pool_cleanup_null);

    return APR_SUCCESS;
}

apr_status_t isapi_lookup(apr_pool_t *p, server_rec *s, request_rec *r,
                          const char *fpath, isapi_loaded** isa)
{
    apr_status_t rv;
    const char *key;

    if ((rv = apr_thread_mutex_lock(loaded.lock)) != APR_SUCCESS) {
