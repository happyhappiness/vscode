 
         /* For now, if a provider isn't set, we'll be nice and use the file
          * provider.
          */
         if (!current_provider) {
             provider = ap_lookup_provider(AUTHN_PROVIDER_GROUP,
-                                          AUTHN_DEFAULT_PROVIDER, "0");
+                                          AUTHN_DEFAULT_PROVIDER,
+                                          AUTHN_PROVIDER_VERSION);
 
             if (!provider || !provider->check_password) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                               "No Authn provider configured");
                 auth_result = AUTH_GENERAL_ERROR;
                 break;
