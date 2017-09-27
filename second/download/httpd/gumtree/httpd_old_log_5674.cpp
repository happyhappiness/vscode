ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ServerSupportFunction "
                          "HSE_REQ_REFRESH_ISAPI_ACL "
                          "is not supported: %s", r->filename);