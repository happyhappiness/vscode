         addReply(c,shared.emptybulk);
     } else {
         addReplyBulkCBuffer(c,(char*)str+start,end-start+1);
     }
 }
 
-void mgetCommand(redisClient *c) {
+void mgetCommand(client *c) {
     int j;
 
     addReplyMultiBulkLen(c,c->argc-1);
     for (j = 1; j < c->argc; j++) {
         robj *o = lookupKeyRead(c->db,c->argv[j]);
         if (o == NULL) {
             addReply(c,shared.nullbulk);
         } else {
-            if (o->type != REDIS_STRING) {
+            if (o->type != OBJ_STRING) {
                 addReply(c,shared.nullbulk);
             } else {
                 addReplyBulk(c,o);
             }
         }
     }
 }
 
-void msetGenericCommand(redisClient *c, int nx) {
+void msetGenericCommand(client *c, int nx) {
     int j, busykeys = 0;
 
     if ((c->argc % 2) == 0) {
         addReplyError(c,"wrong number of arguments for MSET");
         return;
     }
