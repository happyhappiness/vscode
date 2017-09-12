@@ -195,11 +195,13 @@ void setrangeCommand(redisClient *c) {
     if (getLongFromObjectOrReply(c,c->argv[2],&offset,NULL) != REDIS_OK)
         return;
 
+    if (offset < 0) {
+        addReplyError(c,"offset is out of range");
+        return;
+    }
+
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o == NULL) {
-        /* Negative offset is always 0 for non-existing keys */
-        if (offset < 0) offset = 0;
-
         /* Return 0 when setting nothing on a non-existing string */
         if (sdslen(value) == 0) {
             addReply(c,shared.czero);
@@ -233,15 +235,6 @@ void setrangeCommand(redisClient *c) {
             return;
         }
 
-        /* Convert negative indexes. Note that for SETRANGE, the meaning of a
-         * negative index is a little different than for other commands.
-         * Here, an offset of -1 points to the trailing NULL byte of the
-         * string instead of the last character. */
-        if (offset < 0) {
-            offset = olen+1+offset;
-            if (offset < 0) offset = 0;
-        }
-
         /* Return when the resulting string exceeds allowed size */
         if (checkStringLength(c,offset+sdslen(value)) != REDIS_OK)
             return;