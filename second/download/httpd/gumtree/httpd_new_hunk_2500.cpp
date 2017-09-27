
    case HSE_REQ_EXTENSION_TRIGGER:  /* Added after ISAPI 4.0 */
        /*  Undocumented - defined by the Microsoft Jan '00 Platform SDK
         */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ServerSupportFunction "
                          "HSE_REQ_EXTENSION_TRIGGER "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    default:
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ServerSupportFunction (%d) not supported: "
                          "%s", HSE_code, r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;
    }
}

