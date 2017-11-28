 
     if (!A->valid()) {
         fatalf("ERROR: Invalid ACL: %s\n",
                A->cfgline);
     }
 
-    /* append */
-    while (*head)
-        head = &(*head)->next;
-
+    // add to the global list for searching explicit ACLs by name
+    assert(head && *head == Config.aclList);
+    A->next = *head;
     *head = A;
+
+    // register for centralized cleanup
+    aclRegister(A);
 }
 
 bool
 ACL::isProxyAuth() const
 {
     return false;
 }
 
-ACLList::ACLList() : op (1), _acl (NULL), next (NULL)
-{}
-
-void
-ACLList::negated(bool isNegated)
-{
-    if (isNegated)
-        op = 0;
-    else
-        op = 1;
-}
-
 /* ACL result caching routines */
 
 int
 ACL::matchForCache(ACLChecklist *checklist)
 {
     /* This is a fatal to ensure that cacheMatchAcl calls are _only_
