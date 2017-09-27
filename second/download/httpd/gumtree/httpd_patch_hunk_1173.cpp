                 }
             }
         }
         else if (strcmp(w, "ldap-group") == 0) {
             struct mod_auth_ldap_groupattr_entry_t *ent = (struct mod_auth_ldap_groupattr_entry_t *) sec->groupattr->elts;
             int i;
-            required_ldap = 1;
 
             if (sec->group_attrib_is_dn) {
                 if (req->dn == NULL || strlen(req->dn) == 0) {
                     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                   "[%" APR_PID_T_FMT "] auth_ldap authorise: require group: "
                                   "user's DN has not been defined; failing authorisation",
