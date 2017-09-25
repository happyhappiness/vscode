
    case HSE_REQ_ASYNC_READ_CLIENT:
    {
        apr_uint32_t read = 0;
        int res;
        if (!cid->dconf.fake_async) {
            if (cid->dconf.log_unsupported) 
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                            "ISAPI: asynchronous I/O not supported: %s", 
                            r->filename);
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
            return 0;
        }

        if (r->remaining < *buf_size) {
