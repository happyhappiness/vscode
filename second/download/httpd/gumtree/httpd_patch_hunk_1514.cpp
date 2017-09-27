 #if APR_HAS_THREADS
         apr_thread_mutex_lock(sec->lock);
 #endif
         grp = apr_array_push(sec->groupattr);
         grp->name = "member";
         grp = apr_array_push(sec->groupattr);
-        grp->name = "uniquemember";
+        grp->name = "uniqueMember";
+#if APR_HAS_THREADS
+        apr_thread_mutex_unlock(sec->lock);
+#endif
+    }
+
+    /*
+     * If there are no elements in the sub group classes array, the default
+     * should be groupOfNames and groupOfUniqueNames; populate the array now.
+     */
+    if (sec->subgroupclasses->nelts == 0) {
+        struct mod_auth_ldap_groupattr_entry_t *grp;
+#if APR_HAS_THREADS
+        apr_thread_mutex_lock(sec->lock);
+#endif
+        grp = apr_array_push(sec->subgroupclasses);
+        grp->name = "groupOfNames";
+        grp = apr_array_push(sec->subgroupclasses);
+        grp->name = "groupOfUniqueNames";
 #if APR_HAS_THREADS
         apr_thread_mutex_unlock(sec->lock);
 #endif
     }
 
     /*
      * If we have been authenticated by some other module than mod_auth_ldap,
      * the req structure needed for authorization needs to be created
      * and populated with the userid and DN of the account in LDAP
      */
 
     /* Check that we have a userid to start with */
-    if ((!r->user) || (strlen(r->user) == 0)) {
+    if (!r->user) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+            "access to %s failed, reason: no authenticated user", r->uri);
+        return AUTHZ_DENIED;
+    }
+
+    if (!strlen(r->user)) {
         ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
             "ldap authorize: Userid is blank, AuthType=%s",
             r->ap_auth_type);
     }
 
     if(!req) {
