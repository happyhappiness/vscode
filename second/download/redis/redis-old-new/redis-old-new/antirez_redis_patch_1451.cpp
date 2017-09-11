@@ -1,6 +1,8 @@
 #include "redis.h"
 #include <sys/uio.h>
 
+static void setProtocolError(redisClient *c, int pos);
+
 void *dupClientReplyValue(void *o) {
     incrRefCount((robj*)o);
     return o;
@@ -675,8 +677,13 @@ int processInlineBuffer(redisClient *c) {
     size_t querylen;
 
     /* Nothing to do without a \r\n */
-    if (newline == NULL)
+    if (newline == NULL) {
+        if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+            addReplyError(c,"Protocol error: too big inline request");
+            setProtocolError(c,0);
+        }
         return REDIS_ERR;
+    }
 
     /* Split the input buffer up to the \r\n */
     querylen = newline-(c->querybuf);
@@ -726,8 +733,13 @@ int processMultibulkBuffer(redisClient *c) {
 
         /* Multi bulk length cannot be read without a \r\n */
         newline = strchr(c->querybuf,'\r');
-        if (newline == NULL)
+        if (newline == NULL) {
+            if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+                addReplyError(c,"Protocol error: too big mbulk count string");
+                setProtocolError(c,0);
+            }
             return REDIS_ERR;
+        }
 
         /* Buffer should also contain \n */
         if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
@@ -761,8 +773,13 @@ int processMultibulkBuffer(redisClient *c) {
         /* Read bulk length if unknown */
         if (c->bulklen == -1) {
             newline = strchr(c->querybuf+pos,'\r');
-            if (newline == NULL)
+            if (newline == NULL) {
+                if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
+                    addReplyError(c,"Protocol error: too big bulk count string");
+                    setProtocolError(c,0);
+                }
                 break;
+            }
 
             /* Buffer should also contain \n */
             if (newline-(c->querybuf) > ((signed)sdslen(c->querybuf)-2))
@@ -831,9 +848,9 @@ int processMultibulkBuffer(redisClient *c) {
     if (pos) c->querybuf = sdsrange(c->querybuf,pos,-1);
 
     /* We're done when c->multibulk == 0 */
-    if (c->multibulklen == 0) {
-        return REDIS_OK;
-    }
+    if (c->multibulklen == 0) return REDIS_OK;
+
+    /* Still not read to process the command */
     return REDIS_ERR;
 }
 