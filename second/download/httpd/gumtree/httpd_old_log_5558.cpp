ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ServerSupportFunction "
                          "HSE_REQ_GET_CERT_INFO_EX "
                          "is not supported: %s", r->filename);