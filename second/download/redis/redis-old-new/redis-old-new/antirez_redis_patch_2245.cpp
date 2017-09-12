@@ -5479,6 +5479,7 @@ static void blockForKey(redisClient *c, robj *key, time_t timeout) {
     dictEntry *de;
     list *l;
 
+    printf("blockForKey %p %s\n", c, key->ptr);
     c->blockingkey = key;
     incrRefCount(key);
     c->blockingto = timeout;
@@ -5488,6 +5489,7 @@ static void blockForKey(redisClient *c, robj *key, time_t timeout) {
 
         l = listCreate();
         retval = dictAdd(c->db->blockingkeys,key,l);
+        incrRefCount(key);
         assert(retval == DICT_OK);
     } else {
         l = dictGetEntryVal(de);
@@ -5502,6 +5504,7 @@ static void unblockClient(redisClient *c) {
     dictEntry *de;
     list *l;
 
+    printf("unblockClient %p %s\n", c, c->blockingkey->ptr);
     /* Remove this client from the list of clients waiting for this key. */
     assert(c->blockingkey != NULL);
     de = dictFind(c->db->blockingkeys,c->blockingkey);