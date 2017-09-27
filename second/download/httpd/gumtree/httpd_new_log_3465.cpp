ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ServerSupportFunction "
                          "HSE_REQ_DONE_WITH_SESSION is not supported: %s",
                          r->filename);