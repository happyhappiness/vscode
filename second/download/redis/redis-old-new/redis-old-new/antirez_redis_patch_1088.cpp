@@ -373,9 +373,7 @@ void _redisAssertPrintClientInfo(redisClient *c) {
         char buf[128];
         char *arg;
 
-        if (c->argv[j]->type == REDIS_STRING &&
-            c->argv[j]->encoding == REDIS_ENCODING_RAW)
-        {
+        if (c->argv[j]->type == REDIS_STRING && sdsEncodedObject(c->argv[j])) {
             arg = (char*) c->argv[j]->ptr;
         } else {
             snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
@@ -391,7 +389,7 @@ void redisLogObjectDebugInfo(robj *o) {
     redisLog(REDIS_WARNING,"Object type: %d", o->type);
     redisLog(REDIS_WARNING,"Object encoding: %d", o->encoding);
     redisLog(REDIS_WARNING,"Object refcount: %d", o->refcount);
-    if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_RAW) {
+    if (o->type == REDIS_STRING && sdsEncodedObject(o)) {
         redisLog(REDIS_WARNING,"Object raw string len: %zu", sdslen(o->ptr));
         if (sdslen(o->ptr) < 4096) {
             sds repr = sdscatrepr(sdsempty(),o->ptr,sdslen(o->ptr));