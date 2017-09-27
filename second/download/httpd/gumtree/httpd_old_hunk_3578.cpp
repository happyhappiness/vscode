        }
        return (res >= 0);
    }

    case HSE_REQ_GET_IMPERSONATION_TOKEN:  /* Added in ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ServerSupportFunction "
                          "HSE_REQ_GET_IMPERSONATION_TOKEN "
                          "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

