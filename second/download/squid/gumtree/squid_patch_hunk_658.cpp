         snprintf(searchbase, sizeof(searchbase), "%s,%s", extension_dn, basedn);
     else
         snprintf(searchbase, sizeof(searchbase), "%s", basedn);
 
     if (build_filter(filter, sizeof(filter), searchfilter, member, group) != 0) {
         fprintf(stderr, PROGRAM_NAME ": ERROR: Failed to construct LDAP search filter. filter=\"%s\", user=\"%s\", group=\"%s\"\n", filter, member, group);
-        return 1;
+        return -1;
     }
     debug("group filter '%s', searchbase '%s'\n", filter, searchbase);
 
     rc = ldap_search_s(ld, searchbase, searchscope, filter, searchattr, 1, &res);
     if (rc != LDAP_SUCCESS) {
         if (noreferrals && rc == LDAP_PARTIAL_RESULTS) {
