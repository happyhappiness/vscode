     peerClearRRStart();
 }
 
 static void
 free_peer(CachePeer ** P)
 {
-    CachePeer *p;
-
-    while ((p = *P) != NULL) {
-        *P = p->next;
-#if USE_CACHE_DIGESTS
-
-        cbdataReferenceDone(p->digest);
-#endif
-
-        // the mgr job will notice that its owner is gone and stop
-        PeerPoolMgr::Checkpoint(p->standby.mgr, "peer gone");
-        delete p->standby.pool;
-        cbdataFree(p);
-    }
-
+    delete *P;
+    *P = NULL;
     Config.npeers = 0;
 }
 
 static void
 dump_cachemgrpasswd(StoreEntry * entry, const char *name, Mgr::ActionPasswordList * list)
 {
-    wordlist *w;
-
-    while (list != NULL) {
+    while (list) {
         if (strcmp(list->passwd, "none") && strcmp(list->passwd, "disable"))
             storeAppendPrintf(entry, "%s XXXXXXXXXX", name);
         else
             storeAppendPrintf(entry, "%s %s", name, list->passwd);
 
-        for (w = list->actions; w != NULL; w = w->next) {
-            storeAppendPrintf(entry, " %s", w->key);
-        }
+        for (auto w : list->actions)
+            entry->appendf(" " SQUIDSBUFPH, SQUIDSBUFPRINT(w));
 
         storeAppendPrintf(entry, "\n");
         list = list->next;
     }
 }
 
 static void
 parse_cachemgrpasswd(Mgr::ActionPasswordList ** head)
 {
-    char *passwd = NULL;
-    wordlist *actions = NULL;
-    Mgr::ActionPasswordList *p;
-    Mgr::ActionPasswordList **P;
+    char *passwd = nullptr;
     parse_string(&passwd);
-    parse_wordlist(&actions);
-    p = new Mgr::ActionPasswordList;
+
+    Mgr::ActionPasswordList *p = new Mgr::ActionPasswordList;
     p->passwd = passwd;
-    p->actions = actions;
 
+    while (char *token = ConfigParser::NextQuotedToken())
+        p->actions.push_back(SBuf(token));
+
+    Mgr::ActionPasswordList **P;
     for (P = head; *P; P = &(*P)->next) {
         /*
          * See if any of the actions from this line already have a
          * password from previous lines.  The password checking
          * routines in cache_manager.c take the the password from
          * the first Mgr::ActionPasswordList that contains the
          * requested action.  Thus, we should warn users who might
          * think they can have two passwords for the same action.
          */
-        wordlist *w;
-        wordlist *u;
-
-        for (w = (*P)->actions; w; w = w->next) {
-            for (u = actions; u; u = u->next) {
-                if (strcmp(w->key, u->key))
+        for (const auto &w : (*P)->actions) {
+            for (const auto &u : p->actions) {
+                if (w != u)
                     continue;
 
-                debugs(0, DBG_CRITICAL, "WARNING: action '" << u->key << "' (line " << config_lineno << ") already has a password");
+                debugs(0, DBG_PARSE_NOTE(1), "ERROR: action '" << u << "' (line " << config_lineno << ") already has a password");
             }
         }
     }
 
     *P = p;
 }
 
 static void
 free_cachemgrpasswd(Mgr::ActionPasswordList ** head)
 {
-    Mgr::ActionPasswordList *p;
-
-    while ((p = *head) != NULL) {
-        *head = p->next;
-        xfree(p->passwd);
-        wordlistDestroy(&p->actions);
-        xfree(p);
-    }
+    delete *head;
+    *head = nullptr;
 }
 
 static void
 dump_denyinfo(StoreEntry * entry, const char *name, AclDenyInfoList * var)
 {
-    AclNameList *a;
-
     while (var != NULL) {
         storeAppendPrintf(entry, "%s %s", name, var->err_page_name);
 
-        for (a = var->acl_list; a != NULL; a = a->next)
+        for (auto *a = var->acl_list; a != NULL; a = a->next)
             storeAppendPrintf(entry, " %s", a->name);
 
         storeAppendPrintf(entry, "\n");
 
         var = var->next;
     }
