ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "ServerSupportFunction HSE_REQ_GET_SSPI_INFO "
                           "is not supported: %s", r->filename);