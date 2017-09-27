                 "Set to off to disable auth_ldap, even if it's been enabled in a higher tree"),
 
    AP_INIT_FLAG("AuthLDAPFrontPageHack", ap_set_flag_slot,
                 (void *)APR_OFFSETOF(mod_auth_ldap_config_t, frontpage_hack), OR_AUTHCFG,
                 "Set to 'on' to support Microsoft FrontPage"),

    AP_INIT_TAKE1("AuthLDAPCharsetConfig", set_charset_config, NULL, RSRC_CONF,
                  "Character set conversion configuration file. If omitted, character set"
                  "conversion is disabled."),

    {NULL}
};

static int auth_ldap_post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    ap_configfile_t *f;
    char l[MAX_STRING_LEN];
    const char *charset_confname = ap_get_module_config(s->module_config,
                                                      &auth_ldap_module);
    apr_status_t status;
    
    /*
    mod_auth_ldap_config_t *sec = (mod_auth_ldap_config_t *)
                                    ap_get_module_config(s->module_config, 
                                                         &auth_ldap_module);

    if (sec->secure)
    {
        if (!util_ldap_ssl_supported(s))
        {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
                     "LDAP: SSL connections (ldaps://) not supported by utilLDAP");
            return(!OK);
        }
    }
    */

    /* make sure that mod_ldap (util_ldap) is loaded */
    if (ap_find_linked_module("util_ldap.c") == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, s,
                     "Module mod_ldap missing. Mod_ldap (aka. util_ldap) "
                     "must be loaded in order for mod_auth_ldap to function properly");
        return HTTP_INTERNAL_SERVER_ERROR;

    }

    if (!charset_confname) {
        return OK;
    }

    charset_confname = ap_server_root_relative(p, charset_confname);
    if (!charset_confname) {
        ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
                     "Invalid charset conversion config path %s", 
                     (const char *)ap_get_module_config(s->module_config,
                                                        &auth_ldap_module));
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if ((status = ap_pcfg_openfile(&f, ptemp, charset_confname)) 
                != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                     "could not open charset conversion config file %s.", 
                     charset_confname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    charset_conversions = apr_hash_make(p);

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
        const char *ll = l;
        char *lang;

        if (l[0] == '#') {
            continue;
        }
        lang = ap_getword_conf(p, &ll);
        ap_str_tolower(lang);

        if (ll[0]) {
            char *charset = ap_getword_conf(p, &ll);
            apr_hash_set(charset_conversions, lang, APR_HASH_KEY_STRING, charset);
        }
    }
    ap_cfg_closefile(f);
    
    to_charset = derive_codepage_from_lang (p, "utf-8");
    if (to_charset == NULL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, s,
                     "could not find the UTF-8 charset in the file %s.", 
                     charset_confname);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    return OK;
}

static void mod_auth_ldap_register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(auth_ldap_post_config,NULL,NULL,APR_HOOK_MIDDLE);
    ap_hook_check_user_id(mod_auth_ldap_check_user_id, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_auth_checker(mod_auth_ldap_auth_checker, NULL, NULL, APR_HOOK_MIDDLE);
}

module auth_ldap_module = {
   STANDARD20_MODULE_STUFF,
