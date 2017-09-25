                 "Set to off to disable auth_ldap, even if it's been enabled in a higher tree"),
 
    AP_INIT_FLAG("AuthLDAPFrontPageHack", ap_set_flag_slot,
                 (void *)APR_OFFSETOF(mod_auth_ldap_config_t, frontpage_hack), OR_AUTHCFG,
                 "Set to 'on' to support Microsoft FrontPage"),

#ifdef APU_HAS_LDAP_STARTTLS
    AP_INIT_FLAG("AuthLDAPStartTLS", ap_set_flag_slot,
                 (void *)APR_OFFSETOF(mod_auth_ldap_config_t, starttls), OR_AUTHCFG,
                 "Set to 'on' to start TLS after connecting to the LDAP server."),
#endif /* APU_HAS_LDAP_STARTTLS */

    {NULL}
};

static void mod_auth_ldap_register_hooks(apr_pool_t *p)
{
    ap_hook_check_user_id(mod_auth_ldap_check_user_id, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_auth_checker(mod_auth_ldap_auth_checker, NULL, NULL, APR_HOOK_MIDDLE);
}

module auth_ldap_module = {
   STANDARD20_MODULE_STUFF,
