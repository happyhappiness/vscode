    case HSE_REQ_GET_IMPERSONATION_TOKEN:  /* Added in ISAPI 4.0 */
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction "
                          "HSE_REQ_GET_IMPERSONATION_TOKEN "
                          "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_MAP_URL_TO_PATH_EX:
    {
        /* Map a URL to a filename */
        HSE_URL_MAPEX_INFO *info = (HSE_URL_MAPEX_INFO*)data_type;
