        }
    }
    */

    /* make sure that mod_ldap (util_ldap) is loaded */
    if (ap_find_linked_module("util_ldap.c") == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01749)
                     "Module mod_ldap missing. Mod_ldap (aka. util_ldap) "
                     "must be loaded in order for mod_authnz_ldap to function properly");
        return HTTP_INTERNAL_SERVER_ERROR;

    }

    if (!charset_confname) {
        return OK;
    }

    charset_confname = ap_server_root_relative(p, charset_confname);
    if (!charset_confname) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s, APLOGNO(01750)
                     "Invalid charset conversion config path %s",
                     (const char *)ap_get_module_config(s->module_config,
                                                        &authnz_ldap_module));
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if ((status = ap_pcfg_openfile(&f, ptemp, charset_confname))
                != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s, APLOGNO(01751)
                     "could not open charset conversion config file %s.",
                     charset_confname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    charset_conversions = apr_hash_make(p);
