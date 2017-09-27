            return 1;
        }
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                      "ISAPI: ServerSupportFunction HSE_REQ_IO_COMPLETION "
                      "is not supported: %s", r->filename);
        SetLastError(ERROR_INVALID_PARAMETER);
        return 0;

    case HSE_REQ_TRANSMIT_FILE:
    {
        /* we do nothing with (tf->dwFlags & HSE_DISCONNECT_AFTER_SEND)
         */
        HSE_TF_INFO *tf = (HSE_TF_INFO*)buf_data;
        apr_uint32_t sent = 0;
        apr_ssize_t ate = 0;
        apr_status_t rv;
        apr_bucket_brigade *bb;
        apr_bucket *b;
        apr_file_t *fd;
        apr_off_t fsize;

        if (!cid->dconf.fake_async && (tf->dwFlags & HSE_IO_ASYNC)) {
            if (cid->dconf.log_unsupported)
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                         "ISAPI: ServerSupportFunction HSE_REQ_TRANSMIT_FILE "
                         "as HSE_IO_ASYNC is not supported: %s", r->filename);
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }

        /* Presume the handle was opened with the CORRECT semantics
         * for TransmitFile
         */
