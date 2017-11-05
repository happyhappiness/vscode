static apr_status_t isapi_load(apr_pool_t *p, server_rec *s, isapi_loaded *isa)
{
    apr_status_t rv;

    isa->isapi_version = apr_pcalloc(p, sizeof(HSE_VERSION_INFO));

    /* TODO: These aught to become overrideable, so that we
     * assure a given isapi can be fooled into behaving well.
     *
     * The tricky bit, they aren't really a per-dir sort of
     * config, they will always be constant across every
     * reference to the .dll no matter what context (vhost,
     * location, etc) they apply to.
     */
    isa->report_version = 0x500; /* Revision 5.0 */
    isa->timeout = 300 * 1000000; /* microsecs, not used */

    rv = apr_dso_load(&isa->handle, isa->filename, p);
    if (rv)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: failed to load %s", isa->filename);
        isa->handle = NULL;
        return rv;
    }

    rv = apr_dso_sym((void**)&isa->GetExtensionVersion, isa->handle,
                     "GetExtensionVersion");
    if (rv)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: missing GetExtensionVersion() in %s",
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

    rv = apr_dso_sym((void**)&isa->HttpExtensionProc, isa->handle,
                     "HttpExtensionProc");
    if (rv)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: missing HttpExtensionProc() in %s",
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

    /* TerminateExtension() is an optional interface */
    rv = apr_dso_sym((void**)&isa->TerminateExtension, isa->handle,
                     "TerminateExtension");
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