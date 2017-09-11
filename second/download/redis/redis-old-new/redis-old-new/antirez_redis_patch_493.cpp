@@ -34,7 +34,7 @@
  * String Commands
  *----------------------------------------------------------------------------*/
 
-static int checkStringLength(redisClient *c, long long size) {
+static int checkStringLength(client *c, long long size) {
     if (size > 512*1024*1024) {
         addReplyError(c,"string exceeds maximum allowed size (512MB)");
         return REDIS_ERR;
@@ -64,7 +64,7 @@ static int checkStringLength(redisClient *c, long long size) {
 #define REDIS_SET_EX (1<<2)     /* Set if time in seconds is given */
 #define REDIS_SET_PX (1<<3)     /* Set if time in ms in given */
 
-void setGenericCommand(redisClient *c, int flags, robj *key, robj *val, robj *expire, int unit, robj *ok_reply, robj *abort_reply) {
+void setGenericCommand(client *c, int flags, robj *key, robj *val, robj *expire, int unit, robj *ok_reply, robj *abort_reply) {
     long long milliseconds = 0; /* initialized to avoid any harmness warning */
 
     if (expire) {
@@ -93,7 +93,7 @@ void setGenericCommand(redisClient *c, int flags, robj *key, robj *val, robj *ex
 }
 
 /* SET key value [NX] [XX] [EX <seconds>] [PX <milliseconds>] */
-void setCommand(redisClient *c) {
+void setCommand(client *c) {
     int j;
     robj *expire = NULL;
     int unit = UNIT_SECONDS;
@@ -139,22 +139,22 @@ void setCommand(redisClient *c) {
     setGenericCommand(c,flags,c->argv[1],c->argv[2],expire,unit,NULL,NULL);
 }
 
-void setnxCommand(redisClient *c) {
+void setnxCommand(client *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setGenericCommand(c,REDIS_SET_NX,c->argv[1],c->argv[2],NULL,0,shared.cone,shared.czero);
 }
 
-void setexCommand(redisClient *c) {
+void setexCommand(client *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
     setGenericCommand(c,REDIS_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS,NULL,NULL);
 }
 
-void psetexCommand(redisClient *c) {
+void psetexCommand(client *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
     setGenericCommand(c,REDIS_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS,NULL,NULL);
 }
 
-int getGenericCommand(redisClient *c) {
+int getGenericCommand(client *c) {
     robj *o;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL)
@@ -169,19 +169,19 @@ int getGenericCommand(redisClient *c) {
     }
 }
 
-void getCommand(redisClient *c) {
+void getCommand(client *c) {
     getGenericCommand(c);
 }
 
-void getsetCommand(redisClient *c) {
+void getsetCommand(client *c) {
     if (getGenericCommand(c) == REDIS_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
     setKey(c->db,c->argv[1],c->argv[2]);
     notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",c->argv[1],c->db->id);
     server.dirty++;
 }
 
-void setrangeCommand(redisClient *c) {
+void setrangeCommand(client *c) {
     robj *o;
     long offset;
     sds value = c->argv[3]->ptr;
@@ -241,7 +241,7 @@ void setrangeCommand(redisClient *c) {
     addReplyLongLong(c,sdslen(o->ptr));
 }
 
-void getrangeCommand(redisClient *c) {
+void getrangeCommand(client *c) {
     robj *o;
     long long start, end;
     char *str, llbuf[32];
@@ -278,7 +278,7 @@ void getrangeCommand(redisClient *c) {
     }
 }
 
-void mgetCommand(redisClient *c) {
+void mgetCommand(client *c) {
     int j;
 
     addReplyMultiBulkLen(c,c->argc-1);
@@ -296,7 +296,7 @@ void mgetCommand(redisClient *c) {
     }
 }
 
-void msetGenericCommand(redisClient *c, int nx) {
+void msetGenericCommand(client *c, int nx) {
     int j, busykeys = 0;
 
     if ((c->argc % 2) == 0) {
@@ -326,15 +326,15 @@ void msetGenericCommand(redisClient *c, int nx) {
     addReply(c, nx ? shared.cone : shared.ok);
 }
 
-void msetCommand(redisClient *c) {
+void msetCommand(client *c) {
     msetGenericCommand(c,0);
 }
 
-void msetnxCommand(redisClient *c) {
+void msetnxCommand(client *c) {
     msetGenericCommand(c,1);
 }
 
-void incrDecrCommand(redisClient *c, long long incr) {
+void incrDecrCommand(client *c, long long incr) {
     long long value, oldvalue;
     robj *o, *new;
 
@@ -372,29 +372,29 @@ void incrDecrCommand(redisClient *c, long long incr) {
     addReply(c,shared.crlf);
 }
 
-void incrCommand(redisClient *c) {
+void incrCommand(client *c) {
     incrDecrCommand(c,1);
 }
 
-void decrCommand(redisClient *c) {
+void decrCommand(client *c) {
     incrDecrCommand(c,-1);
 }
 
-void incrbyCommand(redisClient *c) {
+void incrbyCommand(client *c) {
     long long incr;
 
     if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
     incrDecrCommand(c,incr);
 }
 
-void decrbyCommand(redisClient *c) {
+void decrbyCommand(client *c) {
     long long incr;
 
     if (getLongLongFromObjectOrReply(c, c->argv[2], &incr, NULL) != REDIS_OK) return;
     incrDecrCommand(c,-incr);
 }
 
-void incrbyfloatCommand(redisClient *c) {
+void incrbyfloatCommand(client *c) {
     long double incr, value;
     robj *o, *new, *aux;
 
@@ -428,7 +428,7 @@ void incrbyfloatCommand(redisClient *c) {
     rewriteClientCommandArgument(c,2,new);
 }
 
-void appendCommand(redisClient *c) {
+void appendCommand(client *c) {
     size_t totlen;
     robj *o, *append;
 
@@ -461,7 +461,7 @@ void appendCommand(redisClient *c) {
     addReplyLongLong(c,totlen);
 }
 
-void strlenCommand(redisClient *c) {
+void strlenCommand(client *c) {
     robj *o;
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
         checkType(c,o,REDIS_STRING)) return;