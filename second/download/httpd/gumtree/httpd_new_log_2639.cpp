ap_log_rerror(APLOG_MARK, APLOG_WARNING, apr_get_os_error(), r,
                          "ISAPI: unrecognized result code %d "
                          "from HttpExtensionProc(): %s ", 
                          rv, r->filename);