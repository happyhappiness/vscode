        if (cid->dconf.fake_async) {
            cid->completion = (PFN_HSE_IO_COMPLETION) buf_data;
            cid->completion_arg = (void *) data_type;
            return 1;
        }
        if (cid->dconf.log_unsupported)
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02673)
                      "ServerSupportFunction HSE_REQ_IO_COMPLETION "
                      "is not supported: %s", r->filename);
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
        return 0;

    case HSE_REQ_TRANSMIT_FILE:
