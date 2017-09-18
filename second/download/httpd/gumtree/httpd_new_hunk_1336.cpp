                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                         "ISAPI: ServerSupportFunction HSE_REQ_TRANSMIT_FILE "
                         "as HSE_IO_ASYNC is not supported: %s", r->filename);
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
            return 0;
        }

        /* Presume the handle was opened with the CORRECT semantics
         * for TransmitFile
         */
        if ((rv = apr_os_file_put(&fd, &tf->hFile,
                                  APR_READ | APR_XTHREAD, r->pool))
                != APR_SUCCESS) {
            return 0;
        }
        if (tf->BytesToWrite) {
            fsize = tf->BytesToWrite;
        }
