             }
         }
         if (use_extension_dn) {
             extension_dn = strtok(NULL, " \n");
             if (!extension_dn) {
                 debug("%s: Invalid request: Extension DN configured, but none sent.\n", argv[0]);
-                SEND_ERR("Invalid Request. Extension DN required.");
+                SEND_BH(HLP_MSG("Invalid Request. Extension DN required"));
                 continue;
             }
             rfc1738_unescape(extension_dn);
         }
+        const char *broken = nullptr;
         while (!found && user && (group = strtok(NULL, " \n")) != NULL) {
             rfc1738_unescape(group);
 
 recover:
             if (ld == NULL) {
 #if HAS_URI_SUPPORT
                 if (strstr(ldapServer, "://") != NULL) {
                     rc = ldap_initialize(&ld, ldapServer);
                     if (rc != LDAP_SUCCESS) {
+                        broken = HLP_MSG("Unable to connect to LDAP server");
                         fprintf(stderr, "%s: ERROR: Unable to connect to LDAPURI:%s\n", argv[0], ldapServer);
                         break;
                     }
                 } else
 #endif
 #if NETSCAPE_SSL
