         storeAppendPrintf(entry, "\n");
         list = list->next;
     }
 }
 
 static void
-parse_cachemgrpasswd(cachemgr_passwd ** head)
+parse_cachemgrpasswd(Mgr::ActionPasswordList ** head)
 {
     char *passwd = NULL;
     wordlist *actions = NULL;
-    cachemgr_passwd *p;
-    cachemgr_passwd **P;
+    Mgr::ActionPasswordList *p;
+    Mgr::ActionPasswordList **P;
     parse_string(&passwd);
     parse_wordlist(&actions);
-    p = static_cast<cachemgr_passwd *>(xcalloc(1, sizeof(cachemgr_passwd)));
+    p = new Mgr::ActionPasswordList;
     p->passwd = passwd;
     p->actions = actions;
 
     for (P = head; *P; P = &(*P)->next) {
         /*
          * See if any of the actions from this line already have a
          * password from previous lines.  The password checking
          * routines in cache_manager.c take the the password from
-         * the first cachemgr_passwd struct that contains the
+         * the first Mgr::ActionPasswordList that contains the
          * requested action.  Thus, we should warn users who might
          * think they can have two passwords for the same action.
          */
         wordlist *w;
         wordlist *u;
 
         for (w = (*P)->actions; w; w = w->next) {
             for (u = actions; u; u = u->next) {
                 if (strcmp(w->key, u->key))
                     continue;
 
-                debugs(0, 0, "WARNING: action '" << u->key << "' (line " << config_lineno << ") already has a password");
+                debugs(0, DBG_CRITICAL, "WARNING: action '" << u->key << "' (line " << config_lineno << ") already has a password");
             }
         }
     }
 
     *P = p;
 }
 
 static void
-free_cachemgrpasswd(cachemgr_passwd ** head)
+free_cachemgrpasswd(Mgr::ActionPasswordList ** head)
 {
-    cachemgr_passwd *p;
+    Mgr::ActionPasswordList *p;
 
     while ((p = *head) != NULL) {
         *head = p->next;
         xfree(p->passwd);
         wordlistDestroy(&p->actions);
         xfree(p);
     }
 }
 
 static void
-dump_denyinfo(StoreEntry * entry, const char *name, acl_deny_info_list * var)
+dump_denyinfo(StoreEntry * entry, const char *name, AclDenyInfoList * var)
 {
-    acl_name_list *a;
+    AclNameList *a;
 
     while (var != NULL) {
         storeAppendPrintf(entry, "%s %s", name, var->err_page_name);
 
         for (a = var->acl_list; a != NULL; a = a->next)
             storeAppendPrintf(entry, " %s", a->name);
