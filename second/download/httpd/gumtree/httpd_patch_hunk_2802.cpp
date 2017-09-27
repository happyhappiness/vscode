         result = uldap_cache_compare(r, ldc, url, group, attrib, value);
         if (result == LDAP_COMPARE_TRUE) {
             /*
              * 4.A. We found the user in the subgroup. Return
              * LDAP_COMPARE_TRUE.
              */
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01295)
                           "Found user %s in a subgroup (%s) at level %d of %d.",
                           r->user, group, cur_subgroup_depth+1,
                           max_subgroup_depth);
         }
         else {
             /*
              * 4.B. We didn't find the user in this subgroup, so recurse into
              * it and keep looking.
              */
-            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01296)
                           "User %s not found in subgroup (%s) at level %d of "
                           "%d.", r->user, group, cur_subgroup_depth+1,
                           max_subgroup_depth);
             result = uldap_cache_check_subgroups(r, ldc, url, group, attrib,
                                                  value, subgroupAttrs,
                                                  subgroupclasses,
