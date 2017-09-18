        return rv;
    }

    /* TerminateExtension() is an optional interface */
    rv = apr_dso_sym((void**)&isa->TerminateExtension, isa->handle,
                     "TerminateExtension");
    SetLastError(0);

    /* Run GetExtensionVersion() */
    if (!(isa->GetExtensionVersion)(isa->isapi_version)) {
        apr_status_t rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
                     "ISAPI: failed call to GetExtensionVersion() in %s", 
