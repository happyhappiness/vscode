ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s, APLOGNO(01750)
                     "Invalid charset conversion config path %s",
                     (const char *)ap_get_module_config(s->module_config,
                                                        &authnz_ldap_module));