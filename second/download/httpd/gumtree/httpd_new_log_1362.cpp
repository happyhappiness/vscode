ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                     "Invalid charset conversion config path %s", 
                     (const char *)ap_get_module_config(s->module_config,
                                                        &auth_ldap_module));