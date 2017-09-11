@@ -1246,12 +1246,13 @@ void pfdebugCommand(redisClient *c) {
     if (!strcasecmp(cmd,"getreg")) {
         if (c->argc != 3) goto arityerr;
 
-        addReplyMultiBulkLen(c,HLL_REGISTERS);
         if (hllSparseToDense(o) == REDIS_ERR) {
             addReplyError(c,"HLL sparse encoding is corrupted");
             return;
         }
+
         hdr = o->ptr;
+        addReplyMultiBulkLen(c,HLL_REGISTERS);
         for (j = 0; j < HLL_REGISTERS; j++) {
             uint8_t val;
 