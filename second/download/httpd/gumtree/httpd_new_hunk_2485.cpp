                     "TerminateExtension");
    apr_set_os_error(0);

    /* Run GetExtensionVersion() */
    if (!(isa->GetExtensionVersion)(isa->isapi_version)) {
        apr_status_t rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(02110)
                     "failed call to GetExtensionVersion() in %s",
                     isa->filename);
        apr_dso_unload(isa->handle);
        isa->handle = NULL;
        return rv;
    }

