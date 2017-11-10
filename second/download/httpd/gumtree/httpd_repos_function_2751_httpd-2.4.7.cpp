static void *util_ldap_create_dir_config(apr_pool_t *p, char *d) {
   util_ldap_config_t *dc =
       (util_ldap_config_t *) apr_pcalloc(p,sizeof(util_ldap_config_t));

   /* defaults are AP_LDAP_CHASEREFERRALS_ON and AP_LDAP_DEFAULT_HOPLIMIT */
   dc->client_certs = apr_array_make(p, 10, sizeof(apr_ldap_opt_tls_cert_t));
   dc->ChaseReferrals = AP_LDAP_CHASEREFERRALS_ON;
   dc->ReferralHopLimit = AP_LDAP_HOPLIMIT_UNSET;

   return dc;
}