        apr_bucket *b;
        apr_file_t *fd;
        apr_off_t fsize;

        if (!cid->dconf.fake_async && (tf->dwFlags & HSE_IO_ASYNC)) {
            if (cid->dconf.log_unsupported)
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                         "ServerSupportFunction HSE_REQ_TRANSMIT_FILE "
                         "as HSE_IO_ASYNC is not supported: %s", r->filename);
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
            return 0;
        }

