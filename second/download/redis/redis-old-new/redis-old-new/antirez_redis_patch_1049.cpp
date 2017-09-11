@@ -391,12 +391,10 @@ void scanCommand(redisClient *c) {
             decrRefCount(kobj);
             listDelNode(keys, ln);
         }
-
         ln = ln_;
     }
 
     addReplyMultiBulkLen(c, 2);
-
     rv = snprintf(buf, sizeof(buf), "%lu", cursor);
     redisAssert(rv < sizeof(buf));
     addReplyBulkCBuffer(c, buf, rv);
@@ -415,7 +413,6 @@ void scanCommand(redisClient *c) {
         decrRefCount(kobj);
         listDelNode(keys, ln);
     }
-
     listRelease(keys);
 }
 