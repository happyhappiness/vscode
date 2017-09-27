ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r,
                          "ISAPI: HSE_STATUS_ERROR result from "
                          "HttpExtensionProc(): %s", r->filename);