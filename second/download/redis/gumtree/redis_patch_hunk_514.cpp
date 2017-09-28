     listIter li1, li2;
     listNode *ln;
 
     /* For every client, check all the waited keys */
     listRewind(server.clients,&li1);
     while((ln = listNext(&li1))) {
-        redisClient *c = listNodeValue(ln);
+        client *c = listNodeValue(ln);
         listRewind(c->watched_keys,&li2);
         while((ln = listNext(&li2))) {
             watchedKey *wk = listNodeValue(ln);
 
             /* For every watched key matching the specified DB, if the
              * key exists, mark the client as dirty, as the key will be
              * removed. */
             if (dbid == -1 || wk->db->id == dbid) {
                 if (dictFind(wk->db->dict, wk->key->ptr) != NULL)
-                    c->flags |= REDIS_DIRTY_CAS;
+                    c->flags |= CLIENT_DIRTY_CAS;
             }
         }
     }
 }
 
-void watchCommand(redisClient *c) {
+void watchCommand(client *c) {
     int j;
 
-    if (c->flags & REDIS_MULTI) {
+    if (c->flags & CLIENT_MULTI) {
         addReplyError(c,"WATCH inside MULTI is not allowed");
         return;
     }
     for (j = 1; j < c->argc; j++)
         watchForKey(c,c->argv[j]);
     addReply(c,shared.ok);
 }
 
-void unwatchCommand(redisClient *c) {
+void unwatchCommand(client *c) {
     unwatchAllKeys(c);
-    c->flags &= (~REDIS_DIRTY_CAS);
+    c->flags &= (~CLIENT_DIRTY_CAS);
     addReply(c,shared.ok);
 }
