             listDelNode(l,ln);
         }
         listRelease(l); /* We have the new list on place at this point. */
     }
 }
 
-int getTimeoutFromObjectOrReply(redisClient *c, robj *object, time_t *timeout) {
-    long tval;
-
-    if (getLongFromObjectOrReply(c,object,&tval,
-        "timeout is not an integer or out of range") != REDIS_OK)
-        return REDIS_ERR;
-
-    if (tval < 0) {
-        addReplyError(c,"timeout is negative");
-        return REDIS_ERR;
-    }
-
-    if (tval > 0) tval += server.unixtime;
-    *timeout = tval;
-
-    return REDIS_OK;
-}
-
 /* Blocking RPOP/LPOP */
 void blockingPopGenericCommand(redisClient *c, int where) {
     robj *o;
-    time_t timeout;
+    mstime_t timeout;
     int j;
 
-    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout) != REDIS_OK)
-        return;
+    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout,UNIT_SECONDS)
+        != REDIS_OK) return;
 
     for (j = 1; j < c->argc-1; j++) {
         o = lookupKeyWrite(c->db,c->argv[j]);
         if (o != NULL) {
             if (o->type != REDIS_LIST) {
                 addReply(c,shared.wrongtypeerr);
