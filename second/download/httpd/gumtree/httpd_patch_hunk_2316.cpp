              * The group entry we want to attach our SGL to doesn't exist.
              * We only got here if we verified this DN was actually a group
              * based on the objectClass, but we can't call the compare function
              * while we already hold the cache lock -- only the insert.
              */
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                          "[%" APR_PID_T_FMT "] util_ldap: Cache entry "
-                          "for %s doesn't exist",
-                           getpid(), dn);
+                          "Cache entry for %s doesn't exist", dn);
             the_compare_node.result = LDAP_COMPARE_TRUE;
             util_ald_cache_insert(curl->compare_cache, &the_compare_node);
             compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                                  &the_compare_node);
             if (compare_nodep == NULL) {
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "[%" APR_PID_T_FMT "] util_ldap: Couldn't "
-                              "retrieve group entry for %s from cache",
-                               getpid(), dn);
+                              "util_ldap: Couldn't retrieve group entry "
+                              "for %s from cache",
+                              dn);
             }
         }
 
         /*
          * We have a valid cache entry and a locally generated SGL.
          * Attach the SGL to the cache entry
