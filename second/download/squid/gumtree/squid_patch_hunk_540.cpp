         self_destruct();
         return;
     }
 
     bumpCfgStyleLast = bumpCfgStyleNow;
 
-    aclParseAclList(LegacyParser, &A->aclList);
+    Acl::AndNode *rule = new Acl::AndNode;
+    rule->context("(ssl_bump rule)", config_input_line);
+    rule->lineParse();
+    // empty rule OK
+
+    assert(ssl_bump);
+    if (!*ssl_bump) {
+        *ssl_bump = new Acl::Tree;
+        (*ssl_bump)->context("(ssl_bump rules)", config_input_line);
+    }
 
-    acl_access *B, **T;
-    for (B = *ssl_bump, T = ssl_bump; B; T = &B->next, B = B->next);
-    *T = A;
+    (*ssl_bump)->add(rule, action);
 }
 
 static void dump_sslproxy_ssl_bump(StoreEntry *entry, const char *name, acl_access *ssl_bump)
 {
-    acl_access *sb;
-    for (sb = ssl_bump; sb != NULL; sb = sb->next) {
-        storeAppendPrintf(entry, "%s ", name);
-        storeAppendPrintf(entry, "%s ", Ssl::bumpMode(sb->allow.kind));
-        if (sb->aclList)
-            dump_acl_list(entry, sb->aclList);
-        storeAppendPrintf(entry, "\n");
+    if (ssl_bump) {
+        wordlist *lines = ssl_bump->treeDump(name, Ssl::BumpModeStr);
+        dump_wordlist(entry, lines);
+        wordlistDestroy(&lines);
     }
 }
 
 static void free_sslproxy_ssl_bump(acl_access **ssl_bump)
 {
     free_acl_access(ssl_bump);
