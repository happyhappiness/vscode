@@ -2956,13 +2956,13 @@ int moduleLoad(const char *path) {
 int moduleUnload(sds name) {
     struct RedisModule *module = dictFetchValue(modules,name);
 
-    if (listLength(module->types)) {
-        errno = EBUSY;
+    if (module == NULL) {
+        errno = ENOENT;
         return REDISMODULE_ERR;
     }
 
-    if (module == NULL) {
-        errno = ENOENT;
+    if (listLength(module->types)) {
+        errno = EBUSY;
         return REDISMODULE_ERR;
     }
 
@@ -3020,10 +3020,17 @@ void moduleCommand(client *c) {
         if (moduleUnload(c->argv[2]->ptr) == C_OK)
             addReply(c,shared.ok);
         else {
-            char *errmsg = "operation not possible.";
+            char *errmsg;
             switch(errno) {
-            case ENOENT: errmsg = "no such module with that name";
-            case EBUSY: errmsg = "the module exports one or more module-side data types, can't unload";
+            case ENOENT:
+                errmsg = "no such module with that name";
+                break;
+            case EBUSY:
+                errmsg = "the module exports one or more module-side data types, can't unload";
+                break;
+            default:
+                errmsg = "operation not possible.";
+                break;
             }
             addReplyErrorFormat(c,"Error unloading module: %s",errmsg);
         }