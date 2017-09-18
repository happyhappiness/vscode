ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "ISAPI: ServerSupportFunction (%d) not supported: "
                          "%s", HSE_code, r->filename);