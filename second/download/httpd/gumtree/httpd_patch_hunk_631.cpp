       "specify an address and/or port with a key pair name.\n"
       "Optional third parameter of MUTUAL configures the port for mutual authentication."),
     AP_INIT_TAKE2("NWSSLUpgradeable", set_secure_upgradeable_listener, NULL, RSRC_CONF,
       "specify an address and/or port with a key pair name, that can be upgraded to an SSL connection.\n"
       "The address and/or port must have already be defined using a Listen directive."),
     AP_INIT_ITERATE("NWSSLTrustedCerts", set_trusted_certs, NULL, RSRC_CONF,
-        "Adds trusted certificates that are used to create secure connections to proxied servers"),
+      "Adds trusted certificates that are used to create secure connections to proxied servers"),
     {NULL}
 };
 
 static void register_hooks(apr_pool_t *p)
 {
     ap_register_output_filter ("UPGRADE_FILTER", ssl_io_filter_Upgrade, NULL, AP_FTYPE_PROTOCOL + 5);
