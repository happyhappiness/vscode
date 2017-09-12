@@ -27,7 +27,7 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#define REDIS_VERSION "1.1.90"
+#define REDIS_VERSION "1.1.91"
 
 #include "fmacros.h"
 #include "config.h"
@@ -1802,7 +1802,7 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
 
             lenobj = createObject(REDIS_STRING,
                 sdscatprintf(sdsempty(),"%lu\r\n",
-                    stringObjectLen(argv[j])));
+                    (unsigned long) stringObjectLen(argv[j])));
             lenobj->refcount = 0;
             outv[outc++] = lenobj;
         }
@@ -2019,7 +2019,7 @@ static void addReplyDouble(redisClient *c, double d) {
 
     snprintf(buf,sizeof(buf),"%.17g",d);
     addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
-        strlen(buf),buf));
+        (unsigned long) strlen(buf),buf));
 }
 
 static void addReplyBulkLen(redisClient *c, robj *obj) {
@@ -2039,7 +2039,7 @@ static void addReplyBulkLen(redisClient *c, robj *obj) {
             len++;
         }
     }
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",len));
+    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",(unsigned long)len));
 }
 
 static void acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -5125,7 +5125,8 @@ static sds genRedisInfoString(void) {
 
 static void infoCommand(redisClient *c) {
     sds info = genRedisInfoString();
-    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",sdslen(info)));
+    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
+        (unsigned long)sdslen(info)));
     addReplySds(c,info);
     addReply(c,shared.crlf);
 }
@@ -5668,7 +5669,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
 
         snprintf(seldb,sizeof(seldb),"%d",dictid);
         buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%lu\r\n%s\r\n",
-            strlen(seldb),seldb);
+            (unsigned long)strlen(seldb),seldb);
         server.appendseldb = dictid;
     }
 
@@ -5692,7 +5693,7 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         robj *o = argv[j];
 
         o = getDecodedObject(o);
-        buf = sdscatprintf(buf,"$%lu\r\n",sdslen(o->ptr));
+        buf = sdscatprintf(buf,"$%lu\r\n",(unsigned long)sdslen(o->ptr));
         buf = sdscatlen(buf,o->ptr,sdslen(o->ptr));
         buf = sdscatlen(buf,"\r\n",2);
         decrRefCount(o);