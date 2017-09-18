ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "a content filter was added without a request: %s", frec->name);