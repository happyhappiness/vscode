     if (AP_LDAP_IS_SERVER_DOWN(result)) { 
         /* connection failed - try again */
         ldc->reason = "ldap_compare_s() failed with server down";
         uldap_connection_unbind(ldc);
         goto start_over;
     }
+    if (result == LDAP_TIMEOUT && failures == 0) {
+        /*
+         * we are reusing a connection that doesn't seem to be active anymore
+         * (firewall state drop?), let's try a new connection.
+         */
+        ldc->reason = "ldap_compare_s() failed with timeout";
+        uldap_connection_unbind(ldc);
+        goto start_over;
+    }
 
     ldc->reason = "Comparison complete";
     if ((LDAP_COMPARE_TRUE == result) ||
         (LDAP_COMPARE_FALSE == result) ||
         (LDAP_NO_SUCH_ATTRIBUTE == result)) {
         if (curl) {
             /* compare completed; caching result */
             LDAP_CACHE_LOCK();
             the_compare_node.lastcompare = curtime;
             the_compare_node.result = result;
+            the_compare_node.sgl_processed = 0;
+            the_compare_node.subgroupList = NULL;
 
             /* If the node doesn't exist then insert it, otherwise just update
              * it with the last results
              */
             compare_nodep = util_ald_cache_fetch(curl->compare_cache,
                                                  &the_compare_node);
             if (   (compare_nodep == NULL)
                 || (strcmp(the_compare_node.dn, compare_nodep->dn) != 0)
                 || (strcmp(the_compare_node.attrib,compare_nodep->attrib) != 0)
                 || (strcmp(the_compare_node.value, compare_nodep->value) != 0))
             {
-                util_ald_cache_insert(curl->compare_cache, &the_compare_node);
+                void *junk;
+
+                junk = util_ald_cache_insert(curl->compare_cache,
+                                             &the_compare_node);
+                if(junk == NULL) {
+                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                                  "[%" APR_PID_T_FMT "] cache_compare: Cache"
+                                  " insertion failure.", getpid());
+                }
             }
             else {
                 compare_nodep->lastcompare = curtime;
                 compare_nodep->result = result;
             }
             LDAP_CACHE_UNLOCK();
