ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, r,
                          "ISAPI ServerSupportFunction (%d) not supported: "
                          "%s", dwHSERequest, r->filename);