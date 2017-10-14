ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(02114)
                               "asynch I/O result HSE_STATUS_PENDING "
                               "from HttpExtensionProc() is not supported: %s",
                               r->filename);