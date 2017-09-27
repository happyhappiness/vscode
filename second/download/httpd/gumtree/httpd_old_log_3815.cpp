ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Unsupported option -%s in file %s",
                      current->token.value, r->filename);