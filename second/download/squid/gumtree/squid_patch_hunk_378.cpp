     }
 
     Config.npeers = 0;
 }
 
 static void
-dump_cachemgrpasswd(StoreEntry * entry, const char *name, cachemgr_passwd * list)
+dump_cachemgrpasswd(StoreEntry * entry, const char *name, Mgr::ActionPasswordList * list)
 {
     wordlist *w;
 
     while (list != NULL) {
         if (strcmp(list->passwd, "none") && strcmp(list->passwd, "disable"))
             storeAppendPrintf(entry, "%s XXXXXXXXXX", name);
