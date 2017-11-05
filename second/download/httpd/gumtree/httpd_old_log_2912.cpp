ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                               "ISAPI: asynch I/O result HSE_STATUS_PENDING "
                               "from HttpExtensionProc() is not supported: %s",
                               r->filename);