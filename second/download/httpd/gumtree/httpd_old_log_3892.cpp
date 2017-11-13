ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                     "Invalid mime types config path %s",
                     (const char *)ap_get_module_config(s->module_config,
                                                        &mime_module));