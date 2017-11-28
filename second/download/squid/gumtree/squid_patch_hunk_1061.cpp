            "' in '" << def->name << "' (ch=" << ch << ").");
 }
 
 static void
 externalAclStats(StoreEntry * sentry)
 {
-    external_acl *p;
-
-    for (p = Config.externalAclHelperList; p; p = p->next) {
+    for (external_acl *p = Config.externalAclHelperList; p; p = p->next) {
         storeAppendPrintf(sentry, "External ACL Statistics: %s\n", p->name);
         storeAppendPrintf(sentry, "Cache size: %d\n", p->cache->count);
-        helperStats(sentry, p->theHelper);
+        assert(p->theHelper);
+        p->theHelper->packStatsInto(sentry);
         storeAppendPrintf(sentry, "\n");
     }
 }
 
 static void
 externalAclRegisterWithCacheManager(void)
