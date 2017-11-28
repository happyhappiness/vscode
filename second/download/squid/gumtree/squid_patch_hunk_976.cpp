 
     if (!xstrtoui(token, NULL, &mark, 0, std::numeric_limits<nfmark_t>::max())) {
         self_destruct();
         return;
     }
 
-    CBDATA_INIT_TYPE_FREECB(acl_nfmark, freed_acl_nfmark);
-
-    l = cbdataAlloc(acl_nfmark);
+    acl_nfmark *l = new acl_nfmark;
 
     l->nfmark = mark;
 
     aclParseAclList(LegacyParser, &l->aclList, token);
 
+    acl_nfmark **tail = head;   /* sane name below */
     while (*tail)
         tail = &(*tail)->next;
 
     *tail = l;
 }
 
 static void
 free_acl_nfmark(acl_nfmark ** head)
 {
-    while (*head) {
-        acl_nfmark *l = *head;
-        *head = l->next;
-        l->next = NULL;
-        cbdataFree(l);
-    }
+    delete *head;
+    *head = NULL;
 }
 #endif /* SO_MARK */
 
-CBDATA_TYPE(AclSizeLimit);
-
 static void
 dump_acl_b_size_t(StoreEntry * entry, const char *name, AclSizeLimit * head)
 {
-    AclSizeLimit *l;
-
-    for (l = head; l; l = l->next) {
+    for (AclSizeLimit *l = head; l; l = l->next) {
         if (l->size != -1)
             storeAppendPrintf(entry, "%s %d %s\n", name, (int) l->size, B_BYTES_STR);
         else
             storeAppendPrintf(entry, "%s none", name);
 
         dump_acl_list(entry, l->aclList);
 
         storeAppendPrintf(entry, "\n");
     }
 }
 
 static void
-freed_acl_b_size_t(void *data)
-{
-    AclSizeLimit *l = static_cast<AclSizeLimit *>(data);
-    aclDestroyAclList(&l->aclList);
-}
-
-static void
 parse_acl_b_size_t(AclSizeLimit ** head)
 {
-    AclSizeLimit *l;
-    AclSizeLimit **tail = head; /* sane name below */
-
-    CBDATA_INIT_TYPE_FREECB(AclSizeLimit, freed_acl_b_size_t);
-
-    l = cbdataAlloc(AclSizeLimit);
+    AclSizeLimit *l = new AclSizeLimit;
 
     parse_b_int64_t(&l->size);
 
     aclParseAclList(LegacyParser, &l->aclList, l->size);
 
+    AclSizeLimit **tail = head; /* sane name below */
     while (*tail)
         tail = &(*tail)->next;
 
     *tail = l;
 }
 
 static void
 free_acl_b_size_t(AclSizeLimit ** head)
 {
-    while (*head) {
-        AclSizeLimit *l = *head;
-        *head = l->next;
-        l->next = NULL;
-        cbdataFree(l);
-    }
+    delete *head;
+    *head = NULL;
 }
 
 #if USE_DELAY_POOLS
 
 #include "DelayConfig.h"
 #include "DelayPools.h"
