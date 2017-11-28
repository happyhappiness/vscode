 
         ;	/* find the tail */
     *T = A;
 }
 
 void
-aclParseAccessLine(ConfigParser &parser, acl_access ** head)
+aclParseAccessLine(const char *directive, ConfigParser &, acl_access **treep)
 {
-    char *t = NULL;
-    acl_access *A = NULL;
-    acl_access *B = NULL;
-    acl_access **T = NULL;
-
     /* first expect either 'allow' or 'deny' */
+    const char *t = ConfigParser::strtokFile();
 
-    if ((t = strtok(NULL, w_space)) == NULL) {
+    if (!t) {
         debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
         debugs(28, DBG_CRITICAL, "aclParseAccessLine: missing 'allow' or 'deny'.");
         return;
     }
 
-    A = new acl_access;
-
+    allow_t action = ACCESS_DUNNO;
     if (!strcmp(t, "allow"))
-        A->allow = ACCESS_ALLOWED;
+        action = ACCESS_ALLOWED;
     else if (!strcmp(t, "deny"))
-        A->allow = ACCESS_DENIED;
+        action = ACCESS_DENIED;
     else {
         debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
         debugs(28, DBG_CRITICAL, "aclParseAccessLine: expecting 'allow' or 'deny', got '" << t << "'.");
-        delete A;
         return;
     }
 
-    aclParseAclList(parser, &A->aclList);
-
-    if (A->aclList == NULL) {
-        debugs(28, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
+    const int ruleId = ((treep && *treep) ? (*treep)->childrenCount() : 0) + 1;
+    MemBuf ctxBuf;
+    ctxBuf.init();
+    ctxBuf.Printf("%s#%d", directive, ruleId);
+    ctxBuf.terminate();
+
+    Acl::AndNode *rule = new Acl::AndNode;
+    rule->context(ctxBuf.content(), config_input_line);
+    rule->lineParse();
+    if (rule->empty()) {
+        debugs(28, DBG_CRITICAL, "aclParseAccessLine: " << cfg_filename << " line " << config_lineno << ": " << config_input_line);
         debugs(28, DBG_CRITICAL, "aclParseAccessLine: Access line contains no ACL's, skipping");
-        delete A;
+        delete rule;
         return;
     }
 
-    A->cfgline = xstrdup(config_input_line);
     /* Append to the end of this list */
 
-    for (B = *head, T = head; B; T = &B->next, B = B->next);
-    *T = A;
+    assert(treep);
+    if (!*treep) {
+        *treep = new Acl::Tree;
+        (*treep)->context(directive, config_input_line);
+    }
+
+    (*treep)->add(rule, action);
 
     /* We lock _acl_access structures in ACLChecklist::matchNonBlocking() */
 }
 
+// aclParseAclList does not expect or set actions (cf. aclParseAccessLine)
 void
-aclParseAclList(ConfigParser &parser, ACLList ** head)
+aclParseAclList(ConfigParser &, Acl::Tree **treep, const char *label)
 {
-    ACLList **Tail = head;	/* sane name in the use below */
-    ACL *a = NULL;
-    char *t;
-
-    /* next expect a list of ACL names, possibly preceeded
-     * by '!' for negation */
-
-    while ((t = strtok(NULL, w_space))) {
-        ACLList *L = new ACLList;
-
-        if (*t == '!') {
-            L->negated (true);
-            ++t;
-        }
-
-        debugs(28, 3, "aclParseAclList: looking for ACL name '" << t << "'");
-        a = ACL::FindByName(t);
+    // accomodate callers unable to convert their ACL list context to string
+    if (!label)
+        label = "...";
+
+    MemBuf ctxLine;
+    ctxLine.init();
+    ctxLine.Printf("(%s %s line)", cfg_directive, label);
+    ctxLine.terminate();
+
+    Acl::AndNode *rule = new Acl::AndNode;
+    rule->context(ctxLine.content(), config_input_line);
+    rule->lineParse();
+
+    MemBuf ctxTree;
+    ctxTree.init();
+    ctxTree.Printf("%s %s", cfg_directive, label);
+    ctxTree.terminate();
+
+    // We want a cbdata-protected Tree (despite giving it only one child node).
+    Acl::Tree *tree = new Acl::Tree;
+    tree->add(rule);
+    tree->context(ctxTree.content(), config_input_line);
+
+    assert(treep);
+    assert(!*treep);
+    *treep = tree;
+}
 
-        if (a == NULL) {
-            debugs(28, DBG_CRITICAL, "aclParseAclList: ACL name '" << t << "' not found.");
-            delete L;
-            parser.destruct();
-            continue;
-        }
+void
+aclRegister(ACL *acl)
+{
+    if (!acl->registered) {
+        if (!RegisteredAcls)
+            RegisteredAcls = new AclSet;
+        RegisteredAcls->insert(acl);
+        acl->registered = true;
+    }
+}
 
-        L->_acl = a;
-        *Tail = L;
-        Tail = &L->next;
+/// remove registered acl from the centralized deletion set
+static
+void
+aclDeregister(ACL *acl)
+{
+    if (acl->registered) {
+        if (RegisteredAcls)
+            RegisteredAcls->erase(acl);
+        acl->registered = false;
     }
 }
 
 /*********************/
 /* Destroy functions */
 /*********************/
 
+/// called to delete ALL Acls.
 void
 aclDestroyAcls(ACL ** head)
 {
-    ACL *next = NULL;
-
-    debugs(28, 8, "aclDestroyACLs: invoked");
-
-    for (ACL *a = *head; a; a = next) {
-        next = a->next;
-        delete a;
+    *head = NULL; // Config.aclList
+    if (AclSet *acls = RegisteredAcls) {
+        debugs(28, 8, "deleting all " << acls->size() << " ACLs");
+        while (!acls->empty()) {
+            ACL *acl = *acls->begin();
+            // We use centralized deletion (this function) so ~ACL should not
+            // delete other ACLs, but we still deregister first to prevent any
+            // accesses to the being-deleted ACL via RegisteredAcls.
+            assert(acl->registered); // make sure we are making progress
+            aclDeregister(acl);
+            delete acl;
+        }
     }
-
-    *head = NULL;
 }
 
 void
-aclDestroyAclList(ACLList ** head)
+aclDestroyAclList(ACLList **list)
 {
-    ACLList *l;
     debugs(28, 8, "aclDestroyAclList: invoked");
-
-    for (l = *head; l; l = *head) {
-        *head = l->next;
-        delete l;
-    }
+    assert(list);
+    delete *list;
+    *list = NULL;
 }
 
 void
 aclDestroyAccessList(acl_access ** list)
 {
-    acl_access *l = NULL;
-    acl_access *next = NULL;
-
-    for (l = *list; l; l = next) {
-        debugs(28, 3, "aclDestroyAccessList: '" << l->cfgline << "'");
-        next = l->next;
-        aclDestroyAclList(&l->aclList);
-        safe_free(l->cfgline);
-        cbdataFree(l);
-    }
-
+    assert(list);
+    if (*list)
+        debugs(28, 3, "destroying: " << *list << ' ' << (*list)->name);
+    delete *list;
     *list = NULL;
 }
 
 /* maex@space.net (06.09.1996)
  *    destroy an AclDenyInfoList */
 
