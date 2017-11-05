ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ISAPI: return code %d from HttpExtensionProc() "
                           "was not not recognized", rv);