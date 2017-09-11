@@ -53,11 +53,11 @@ struct RedisModuleCtx {
 };
 typedef struct RedisModuleCtx RedisModuleCtx;
 
-#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RedisModule_GetApi, NULL, NULL, NULL, 0, 0, 0}
+#define REDISMODULE_CTX_INIT {(void*)(unsigned long)&RM_GetApi, NULL, NULL, NULL, 0, 0, 0}
 #define REDISMODULE_CTX_MULTI_EMITTED (1<<0)
 #define REDISMODULE_CTX_AUTO_MEMORY (1<<1)
 
-/* This represents a Redis key opened with RedisModule_OpenKey(). */
+/* This represents a Redis key opened with RM_OpenKey(). */
 struct RedisModuleKey {
     RedisModuleCtx *ctx;
     redisDb *db;
@@ -85,7 +85,7 @@ typedef struct RedisModuleCommandProxy RedisModuleCommandProxy;
 #define REDISMODULE_REPLYFLAG_NESTED (1<<1)  /* Nested reply object. No proto
                                                 or struct free. */
 
-/* Reply of RedisModule_Call() function. The function is filled in a lazy
+/* Reply of RM_Call() function. The function is filled in a lazy
  * way depending on the function called on the reply structure. By default
  * only the type and proto are filled. */
 struct RedisModuleCallReply {
@@ -110,9 +110,9 @@ typedef struct RedisModuleCallReply RedisModuleCallReply;
  * Prototypes
  * -------------------------------------------------------------------------- */
 
-void RedisModule_FreeCallReply(RedisModuleCallReply *reply);
-void RedisModule_CloseKey(RedisModuleKey *key);
-void RedisModule_AutoMemoryCollect(RedisModuleCtx *ctx);
+void RM_FreeCallReply(RedisModuleCallReply *reply);
+void RM_CloseKey(RedisModuleKey *key);
+void RM_AutoMemoryCollect(RedisModuleCtx *ctx);
 robj **moduleCreateArgvFromUserFormat(const char *cmdname, const char *fmt, int *argcp, int *flags, va_list ap);
 void moduleReplicateMultiIfNeeded(RedisModuleCtx *ctx);
 
@@ -186,12 +186,18 @@ int moduleDelKeyIfEmpty(RedisModuleKey *key) {
 
 /* --------------------------------------------------------------------------
  * Service API exported to modules
+ *
+ * Note that all the exported APIs are called RM_<funcname> in the core
+ * and RedisModule_<funcname> in the module side (defined as function
+ * pointers in redismodule.h). In this way the dynamic linker does not
+ * mess with our global function pointers, overriding it with the symbols
+ * defined in the main executable having the same names.
  * -------------------------------------------------------------------------- */
 
 /* Lookup the requested module API and store the function pointer into the
  * target pointer. The function returns REDISMODULE_ERR if there is no such
  * named API, otherwise REDISMODULE_OK. */
-int RedisModule_GetApi(const char *funcname, void **targetPtrPtr) {
+int RM_GetApi(const char *funcname, void **targetPtrPtr) {
     dictEntry *he = dictFind(server.moduleapi, funcname);
     if (!he) return REDISMODULE_ERR;
     *targetPtrPtr = dictGetVal(he);
@@ -207,7 +213,7 @@ void RedisModuleCommandDispatcher(client *c) {
     ctx.module = cp->module;
     ctx.client = c;
     cp->func(&ctx,(void**)c->argv,c->argc);
-    RedisModule_AutoMemoryCollect(&ctx);
+    RM_AutoMemoryCollect(&ctx);
     preventCommandPropagation(c);
 
     /* Handle the replication of the final EXEC, since whatever a command
@@ -225,7 +231,7 @@ void RedisModuleCommandDispatcher(client *c) {
  * calling the function pointer 'func' using the RedisModule calling
  * convention. The function returns REDISMODULE_ERR if the specified command
  * name is already busy, otherwise REDISMODULE_OK. */
-int RedisModule_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModuleCmdFunc cmdfunc) {
+int RM_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModuleCmdFunc cmdfunc) {
     struct redisCommand *rediscmd;
     RedisModuleCommandProxy *cp;
     sds cmdname = sdsnew(name);
@@ -262,8 +268,8 @@ int RedisModule_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModule
     return REDISMODULE_OK;
 }
 
-/* Called by RedisModule_Init() to setup the ctx->module structure. */
-void RedisModule_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver, int apiver){
+/* Called by RM_Init() to setup the ctx->module structure. */
+void RM_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver, int apiver){
     RedisModule *module;
 
     if (ctx->module != NULL) return;
@@ -279,12 +285,12 @@ void RedisModule_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver
  * -------------------------------------------------------------------------- */
 
 /* Enable auto memory. */
-void RedisModule_AutoMemory(RedisModuleCtx *ctx) {
+void RM_AutoMemory(RedisModuleCtx *ctx) {
     ctx->flags |= REDISMODULE_CTX_AUTO_MEMORY;
 }
 
 /* Add a new object to release automatically when the callback returns. */
-void RedisModule_AutoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
+void RM_AutoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
     if (ctx->amqueue_used == ctx->amqueue_len) {
         ctx->amqueue_len *= 2;
@@ -298,7 +304,7 @@ void RedisModule_AutoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
 
 /* Mark an object as freed in the auto release queue, so that users can still
  * free things manually if they want. */
-void RedisModule_AutoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
+void RM_AutoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
 
     int j;
@@ -315,7 +321,7 @@ void RedisModule_AutoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
 }
 
 /* Release all the objects in queue. */
-void RedisModule_AutoMemoryCollect(RedisModuleCtx *ctx) {
+void RM_AutoMemoryCollect(RedisModuleCtx *ctx) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
     /* Clear the AUTO_MEMORY flag from the context, otherwise the functions
      * we call to free the resources, will try to scan the auto release
@@ -326,8 +332,8 @@ void RedisModule_AutoMemoryCollect(RedisModuleCtx *ctx) {
         void *ptr = ctx->amqueue[j].ptr;
         switch(ctx->amqueue[j].type) {
         case REDISMODULE_AM_STRING: decrRefCount(ptr); break;
-        case REDISMODULE_AM_REPLY: RedisModule_FreeCallReply(ptr); break;
-        case REDISMODULE_AM_KEY: RedisModule_CloseKey(ptr); break;
+        case REDISMODULE_AM_REPLY: RM_FreeCallReply(ptr); break;
+        case REDISMODULE_AM_KEY: RM_CloseKey(ptr); break;
         }
     }
     ctx->flags |= REDISMODULE_CTX_AUTO_MEMORY;
@@ -342,31 +348,31 @@ void RedisModule_AutoMemoryCollect(RedisModuleCtx *ctx) {
  * -------------------------------------------------------------------------- */
 
 /* Create a new module string object. Must be freed with
- * RedisModule_FreeString(), unless automatic memory is enabled. */
-RedisModuleString *RedisModule_CreateString(RedisModuleCtx *ctx, const char *ptr, size_t len)
+ * RM_FreeString(), unless automatic memory is enabled. */
+RedisModuleString *RM_CreateString(RedisModuleCtx *ctx, const char *ptr, size_t len)
 {
     RedisModuleString *o = createStringObject(ptr,len);
-    RedisModule_AutoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
+    RM_AutoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
     return o;
 }
 
-/* Like RedisModule_CreatString, but creates a string starting from a long long
+/* Like RM_CreatString, but creates a string starting from a long long
  * integer instea of taking a buffer and length. */
-RedisModuleString *RedisModule_CreateStringFromLongLong(RedisModuleCtx *ctx, long long ll) {
+RedisModuleString *RM_CreateStringFromLongLong(RedisModuleCtx *ctx, long long ll) {
     char buf[LONG_STR_SIZE];
     size_t len = ll2string(buf,sizeof(buf),ll);
-    return RedisModule_CreateString(ctx,buf,len);
+    return RM_CreateString(ctx,buf,len);
 }
 
 /* Free a module string object obtained with one of the Redis API calls
  * that return new string objects. */
-void RedisModule_FreeString(RedisModuleCtx *ctx, RedisModuleString *str) {
+void RM_FreeString(RedisModuleCtx *ctx, RedisModuleString *str) {
     decrRefCount(str);
-    RedisModule_AutoMemoryFreed(ctx,REDISMODULE_AM_STRING,str);
+    RM_AutoMemoryFreed(ctx,REDISMODULE_AM_STRING,str);
 }
 
 /* Return the string pointer and length. */
-const char *RedisModule_StringPtrLen(RedisModuleString *str, size_t *len) {
+const char *RM_StringPtrLen(RedisModuleString *str, size_t *len) {
     if (len) *len = sdslen(str->ptr);
     return str->ptr;
 }
@@ -375,7 +381,7 @@ const char *RedisModule_StringPtrLen(RedisModuleString *str, size_t *len) {
  * Returns REDISMODULE_OK on success. If the string can't be parsed
  * as a valid, strict long long (no spaces before/after), REDISMODULE_ERR
  * is returned. */
-int RedisModule_StringToLongLong(RedisModuleString *str, long long *ll) {
+int RM_StringToLongLong(RedisModuleString *str, long long *ll) {
     return string2ll(str->ptr,sdslen(str->ptr),ll) ? REDISMODULE_OK :
                                                      REDISMODULE_ERR;
 }
@@ -387,11 +393,11 @@ int RedisModule_StringToLongLong(RedisModuleString *str, long long *ll) {
  * 'return' in order to return from the command implementation with:
  *
  * if (... some condition ...)
- *     return RedisModule_ReplyWithLongLong(ctx,mycount);
+ *     return RM_ReplyWithLongLong(ctx,mycount);
  * -------------------------------------------------------------------------- */
 
 /* Send an error about the number of arguments given to the command. */
-int RedisModule_WrongArity(RedisModuleCtx *ctx) {
+int RM_WrongArity(RedisModuleCtx *ctx) {
     addReplyErrorFormat(ctx->client,
         "wrong number of arguments for '%s' command",
         (char*)ctx->client->argv[0]->ptr);
@@ -400,14 +406,14 @@ int RedisModule_WrongArity(RedisModuleCtx *ctx) {
 
 /* Send an integer reply with the specified long long value.
  * The function always returns REDISMODULE_OK. */
-int RedisModule_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
+int RM_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
     addReplyLongLong(ctx->client,ll);
     return REDISMODULE_OK;
 }
 
 /* Reply with an error or simple string (status message). Used to implement
  * ReplyWithSimpleString() and ReplyWithError(). */
-int RedisModule_ReplyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
+int RM_ReplyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
     sds strmsg = sdsnewlen(prefix,1);
     strmsg = sdscat(strmsg,msg);
     strmsg = sdscatlen(strmsg,"\r\n",2);
@@ -421,39 +427,39 @@ int RedisModule_ReplyWithStatus(RedisModuleCtx *ctx, const char *msg, char *pref
  * the initial error code. The function only provides the initial "-", so
  * the usage is, for example:
  *
- * RedisModule_ReplyWithError(ctx,"ERR Wrong Type");
+ * RM_ReplyWithError(ctx,"ERR Wrong Type");
  *
  * and not just:
  *
- * RedisModule_ReplyWithError(ctx,"Wrong Type");
+ * RM_ReplyWithError(ctx,"Wrong Type");
  */
-int RedisModule_ReplyWithError(RedisModuleCtx *ctx, const char *err) {
-    return RedisModule_ReplyWithStatus(ctx,err,"-");
+int RM_ReplyWithError(RedisModuleCtx *ctx, const char *err) {
+    return RM_ReplyWithStatus(ctx,err,"-");
 }
 
 /* Reply with a simple string (+... \r\n in RESP protocol). This replies
  * are suitalbe only when sending a small non-binary string wiht small
  * overhead, like "OK" or similar replies. */
-int RedisModule_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
-    return RedisModule_ReplyWithStatus(ctx,msg,"+");
+int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
+    return RM_ReplyWithStatus(ctx,msg,"+");
 }
 
 /* Reply with an array type of 'len' elements. However 'len' other calls
  * to ReplyWith* style functions must follow in order to emit the elements
  * of the array. */
-int RedisModule_ReplyWithArray(RedisModuleCtx *ctx, int len) {
+int RM_ReplyWithArray(RedisModuleCtx *ctx, int len) {
     addReplyMultiBulkLen(ctx->client,len);
     return REDISMODULE_OK;
 }
 
 /* Reply with a bulk string, taking in input a C buffer pointer and length. */
-int RedisModule_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
+int RM_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
     addReplyBulkCBuffer(ctx->client,(char*)buf,len);
     return REDISMODULE_OK;
 }
 
 /* Reply with a bulk string, taking in input a RedisModuleString object. */
-int RedisModule_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
+int RM_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
     addReplyBulk(ctx->client,str);
     return REDISMODULE_OK;
 }
@@ -476,12 +482,12 @@ void moduleReplicateMultiIfNeeded(RedisModuleCtx *ctx) {
  *
  * The replicated commands are always wrapepd into the MULTI/EXEC that
  * contains all the commands replicated in a given module command
- * execution. However the commands replicated with RedisModule_Call()
- * are the first items, the ones replicated with RedisModule_Replicate()
+ * execution. However the commands replicated with RM_Call()
+ * are the first items, the ones replicated with RM_Replicate()
  * will all follow before the EXEC.
  *
  * Modules should try to use one interface or the other. */
-int RedisModule_Replicate(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...) {
+int RM_Replicate(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...) {
     struct redisCommand *cmd;
     robj **argv = NULL;
     int argc = 0, flags = 0, j;
@@ -511,7 +517,7 @@ int RedisModule_Replicate(RedisModuleCtx *ctx, const char *cmdname, const char *
  * by the client. This function will not wrap the command into
  * a MULTI/EXEC stanza, so it should not be mixed with other replication
  * commands. */
-int RedisModule_ReplicateVerbatim(RedisModuleCtx *ctx) {
+int RM_ReplicateVerbatim(RedisModuleCtx *ctx) {
     alsoPropagate(ctx->client->cmd,ctx->client->db->id,
         ctx->client->argv,ctx->client->argc,
         PROPAGATE_AOF|PROPAGATE_REPL);
@@ -523,13 +529,13 @@ int RedisModule_ReplicateVerbatim(RedisModuleCtx *ctx) {
  * -------------------------------------------------------------------------- */
 
 /* Return the currently selected DB. */
-int RedisModule_GetSelectedDb(RedisModuleCtx *ctx) {
+int RM_GetSelectedDb(RedisModuleCtx *ctx) {
     return ctx->client->db->id;
 }
 
 /* Change the currently selected DB. Returns an error if the id
  * is out of range. */
-int RedisModule_SelectDb(RedisModuleCtx *ctx, int newid) {
+int RM_SelectDb(RedisModuleCtx *ctx, int newid) {
     int retval = selectDb(ctx->client,newid);
     return (retval == C_OK) ? REDISMODULE_OK : REDISMODULE_ERR;
 }
@@ -539,16 +545,16 @@ int RedisModule_SelectDb(RedisModuleCtx *ctx, int newid) {
  * operations on the key.
  *
  * The return value is the handle repesenting the key, that must be
- * closed with RedisModule_CloseKey().
+ * closed with RM_CloseKey().
  *
  * If the key does not exist and WRITE mode is requested, the handle
  * is still returned, since it is possible to perform operations on
  * a yet not existing key (that will be created, for example, after
  * a list push operation). If the mode is just READ instead, and the
  * key does not exist, NULL is returned. However it is still safe to
- * call RedisModule_CloseKey() and RedisModule_KeyType() on a NULL
+ * call RM_CloseKey() and RM_KeyType() on a NULL
  * value. */
-void *RedisModule_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
+void *RM_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
     RedisModuleKey *kp;
     robj *value;
 
@@ -571,23 +577,23 @@ void *RedisModule_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
     kp->value = value;
     kp->iter = NULL;
     kp->mode = mode;
-    RedisModule_AutoMemoryAdd(ctx,REDISMODULE_AM_KEY,kp);
+    RM_AutoMemoryAdd(ctx,REDISMODULE_AM_KEY,kp);
     return (void*)kp;
 }
 
 /* Close a key handle. */
-void RedisModule_CloseKey(RedisModuleKey *key) {
+void RM_CloseKey(RedisModuleKey *key) {
     if (key == NULL) return;
     if (key->mode & REDISMODULE_WRITE) signalModifiedKey(key->db,key->key);
-    /* TODO: if (key->iter) RedisModule_KeyIteratorStop(kp); */
+    /* TODO: if (key->iter) RM_KeyIteratorStop(kp); */
     decrRefCount(key->key);
-    RedisModule_AutoMemoryFreed(key->ctx,REDISMODULE_AM_KEY,key);
+    RM_AutoMemoryFreed(key->ctx,REDISMODULE_AM_KEY,key);
     zfree(key);
 }
 
 /* Return the type of the key. If the key pointer is NULL then
  * REDISMODULE_KEYTYPE_EMPTY is returned. */
-int RedisModule_KeyType(RedisModuleKey *key) {
+int RM_KeyType(RedisModuleKey *key) {
     if (key == NULL || key->value ==  NULL) return REDISMODULE_KEYTYPE_EMPTY;
     /* We map between defines so that we are free to change the internal
      * defines as desired. */
@@ -606,7 +612,7 @@ int RedisModule_KeyType(RedisModuleKey *key) {
  * is the number of elements (just counting keys for hashes).
  *
  * If the key pointer is NULL or the key is empty, zero is returned. */
-size_t RedisModule_ValueLength(RedisModuleKey *key) {
+size_t RM_ValueLength(RedisModuleKey *key) {
     if (key == NULL || key->value == NULL) return 0;
     switch(key->value->type) {
     case OBJ_STRING: return stringObjectLen(key->value);
@@ -622,7 +628,7 @@ size_t RedisModule_ValueLength(RedisModuleKey *key) {
  * accept new writes as an empty key (that will be created on demand).
  * On success REDISMODULE_OK is returned. If the key is not open for
  * writing REDISMODULE_ERR is returned. */
-int RedisModule_DeleteKey(RedisModuleKey *key) {
+int RM_DeleteKey(RedisModuleKey *key) {
     if (!(key->mode & REDISMODULE_WRITE)) return REDISMODULE_ERR;
     if (key->value) {
         dbDelete(key->db,key->key);
@@ -639,9 +645,9 @@ int RedisModule_DeleteKey(RedisModuleKey *key) {
  * value of the key, deleting the old value if any.
  * On success REDISMODULE_OK is returned. If the key is not open for
  * writing or there is an active iterator, REDISMODULE_ERR is returned. */
-int RedisModule_StringSet(RedisModuleKey *key, RedisModuleString *str) {
+int RM_StringSet(RedisModuleKey *key, RedisModuleString *str) {
     if (!(key->mode & REDISMODULE_WRITE) || key->iter) return REDISMODULE_ERR;
-    RedisModule_DeleteKey(key);
+    RM_DeleteKey(key);
     setKey(key->db,key->key,str);
     return REDISMODULE_OK;
 }
@@ -666,16 +672,16 @@ int RedisModule_StringSet(RedisModuleKey *key, RedisModuleString *str) {
  * the pointer is obtained, for all the time we want to use DMA access
  * to read or modify the string.
  *
- * 2. Each time RedisModule_StringTruncate() is called, to continue with the DMA
- * access, RedisModule_StringDMA() should be called again to re-obtain
+ * 2. Each time RM_StringTruncate() is called, to continue with the DMA
+ * access, RM_StringDMA() should be called again to re-obtain
  * a new pointer and length.
  *
  * 3. If the returned pointer is not NULL, but the length is zero, no
  * byte can be touched (the string is empty, or the key itself is empty)
- * so a RedisModule_StringTruncate() call should be used if there is to enlarge
+ * so a RM_StringTruncate() call should be used if there is to enlarge
  * the string, and later call StringDMA() again to get the pointer.
  */
-char *RedisModule_StringDMA(RedisModuleKey *key, size_t *len, int mode) {
+char *RM_StringDMA(RedisModuleKey *key, size_t *len, int mode) {
     /* We need to return *some* pointer for empty keys, we just return
      * a string literal pointer, that is the advantage to be mapped into
      * a read only memory page, so the module will segfault if a write
@@ -700,7 +706,7 @@ char *RedisModule_StringDMA(RedisModuleKey *key, size_t *len, int mode) {
 /* If the string is open for writing and is of string type, resize it, padding
  * with zero bytes if the new length is greater than the old one.
  *
- * After this call, RedisModule_StringDMA() must be called again to continue
+ * After this call, RM_StringDMA() must be called again to continue
  * DMA access with the new pointer.
  *
  * The function returns REDISMODULE_OK on success, and REDISMODULE_ERR on
@@ -709,7 +715,7 @@ char *RedisModule_StringDMA(RedisModuleKey *key, size_t *len, int mode) {
  *
  * If the key is empty, a string key is created with the new string value
  * unless the new length value requested is zero. */
-int RedisModule_StringTruncate(RedisModuleKey *key, size_t newlen) {
+int RM_StringTruncate(RedisModuleKey *key, size_t newlen) {
     if (!(key->mode & REDISMODULE_WRITE)) return REDISMODULE_ERR;
     if (key->value && key->value->type != OBJ_STRING) return REDISMODULE_ERR;
     if (newlen > 512*1024*1024) return REDISMODULE_ERR;
@@ -749,7 +755,7 @@ int RedisModule_StringTruncate(RedisModuleKey *key, size_t newlen) {
  * If the key pointer is about an empty key opened for writing, the key
  * is created. On error (key opened for read-only operations or of the wrong
  * type) REDISMODULE_ERR is returned, otherwise REDISMODULE_OK is returned. */
-int RedisModule_ListPush(RedisModuleKey *key, int where, RedisModuleString *ele) {
+int RM_ListPush(RedisModuleKey *key, int where, RedisModuleString *ele) {
     if (!(key->mode & REDISMODULE_WRITE)) return REDISMODULE_ERR;
     if (key->value == NULL) moduleCreateEmtpyKey(key,REDISMODULE_KEYTYPE_LIST);
     if (key->value->type != OBJ_LIST) return REDISMODULE_ERR;
@@ -760,13 +766,13 @@ int RedisModule_ListPush(RedisModuleKey *key, int where, RedisModuleString *ele)
 }
 
 /* Pop an element from the list, and returns it as a module string object
- * that the user should be free with RedisModule_FreeString() or by enabling
+ * that the user should be free with RM_FreeString() or by enabling
  * automatic memory. 'where' specifies if the element should be popped from
  * head or tail. The command returns NULL if:
  * 1) The list is empty.
  * 2) The key was not open for writing.
  * 3) The key is not a list. */
-RedisModuleString *RedisModule_ListPop(RedisModuleKey *key, int where) {
+RedisModuleString *RM_ListPop(RedisModuleKey *key, int where) {
     if (!(key->mode & REDISMODULE_WRITE) ||
         key->value == NULL ||
         key->value->type != OBJ_LIST) return NULL;
@@ -775,7 +781,7 @@ RedisModuleString *RedisModule_ListPop(RedisModuleKey *key, int where) {
     robj *decoded = getDecodedObject(ele);
     decrRefCount(ele);
     moduleDelKeyIfEmpty(key);
-    RedisModule_AutoMemoryAdd(key->ctx,REDISMODULE_AM_STRING,decoded);
+    RM_AutoMemoryAdd(key->ctx,REDISMODULE_AM_STRING,decoded);
     return decoded;
 }
 
@@ -894,7 +900,7 @@ void moduleParseCallReply_Array(RedisModuleCallReply *reply) {
 
 /* Free a Call reply and all the nested replies it contains if it's an
  * array. */
-void RedisModule_FreeCallReply_Rec(RedisModuleCallReply *reply, int freenested){
+void RM_FreeCallReply_Rec(RedisModuleCallReply *reply, int freenested){
     /* Don't free nested replies by default: the user must always free the
      * toplevel reply. However be gentle and don't crash if the module
      * misuses the API. */
@@ -904,7 +910,7 @@ void RedisModule_FreeCallReply_Rec(RedisModuleCallReply *reply, int freenested){
         if (reply->type == REDISMODULE_REPLY_ARRAY) {
             size_t j;
             for (j = 0; j < reply->len; j++)
-                RedisModule_FreeCallReply_Rec(reply->val.array+j,1);
+                RM_FreeCallReply_Rec(reply->val.array+j,1);
             zfree(reply->val.array);
         }
     }
@@ -922,18 +928,18 @@ void RedisModule_FreeCallReply_Rec(RedisModuleCallReply *reply, int freenested){
 /* Wrapper for the recursive free reply function. This is needed in order
  * to have the first level function to return on nested replies, but only
  * if called by the module API. */
-void RedisModule_FreeCallReply(RedisModuleCallReply *reply) {
-    RedisModule_FreeCallReply_Rec(reply,0);
-    RedisModule_AutoMemoryFreed(reply->ctx,REDISMODULE_AM_REPLY,reply);
+void RM_FreeCallReply(RedisModuleCallReply *reply) {
+    RM_FreeCallReply_Rec(reply,0);
+    RM_AutoMemoryFreed(reply->ctx,REDISMODULE_AM_REPLY,reply);
 }
 
 /* Return the reply type. */
-int RedisModule_CallReplyType(RedisModuleCallReply *reply) {
+int RM_CallReplyType(RedisModuleCallReply *reply) {
     return reply->type;
 }
 
 /* Return the reply type length, where applicable. */
-size_t RedisModule_CallReplyLength(RedisModuleCallReply *reply) {
+size_t RM_CallReplyLength(RedisModuleCallReply *reply) {
     moduleParseCallReply(reply);
     switch(reply->type) {
     case REDISMODULE_REPLY_STRING:
@@ -947,22 +953,22 @@ size_t RedisModule_CallReplyLength(RedisModuleCallReply *reply) {
 
 /* Return the 'idx'-th nested call reply element of an array reply, or NULL
  * if the reply type is wrong or the index is out of range. */
-RedisModuleCallReply *RedisModule_CallReplyArrayElement(RedisModuleCallReply *reply, size_t idx) {
+RedisModuleCallReply *RM_CallReplyArrayElement(RedisModuleCallReply *reply, size_t idx) {
     moduleParseCallReply(reply);
     if (reply->type != REDISMODULE_REPLY_ARRAY) return NULL;
     if (idx >= reply->len) return NULL;
     return reply->val.array+idx;
 }
 
 /* Return the long long of an integer reply. */
-long long RedisModule_CallReplyInteger(RedisModuleCallReply *reply) {
+long long RM_CallReplyInteger(RedisModuleCallReply *reply) {
     moduleParseCallReply(reply);
     if (reply->type != REDISMODULE_REPLY_INTEGER) return LLONG_MIN;
     return reply->val.ll;
 }
 
 /* Return the pointer and length of a string or error reply. */
-const char *RedisModule_CallReplyStringPtr(RedisModuleCallReply *reply, size_t *len) {
+const char *RM_CallReplyStringPtr(RedisModuleCallReply *reply, size_t *len) {
     moduleParseCallReply(reply);
     if (reply->type != REDISMODULE_REPLY_STRING &&
         reply->type != REDISMODULE_REPLY_ERROR) return NULL;
@@ -972,24 +978,24 @@ const char *RedisModule_CallReplyStringPtr(RedisModuleCallReply *reply, size_t *
 
 /* Return a new string object from a call reply of type string, error or
  * integer. Otherwise (wrong reply type) return NULL. */
-RedisModuleString *RedisModule_CreateStringFromCallReply(RedisModuleCallReply *reply) {
+RedisModuleString *RM_CreateStringFromCallReply(RedisModuleCallReply *reply) {
     moduleParseCallReply(reply);
     switch(reply->type) {
     case REDISMODULE_REPLY_STRING:
     case REDISMODULE_REPLY_ERROR:
-        return RedisModule_CreateString(reply->ctx,reply->val.str,reply->len);
+        return RM_CreateString(reply->ctx,reply->val.str,reply->len);
     case REDISMODULE_REPLY_INTEGER: {
         char buf[64];
         int len = ll2string(buf,sizeof(buf),reply->val.ll);
-        return RedisModule_CreateString(reply->ctx,buf,len);
+        return RM_CreateString(reply->ctx,buf,len);
         }
     default: return NULL;
     }
 }
 
 /* Returns an array of robj pointers, and populates *argc with the number
  * of items, by parsing the format specifier "fmt" as described for
- * the RedisModule_Call(), RedisModule_Replicate() and other module APIs.
+ * the RM_Call(), RM_Replicate() and other module APIs.
  *
  * The integer pointed by 'flags' is populated with flags according
  * to special modifiers in "fmt". For now only one exists:
@@ -1056,7 +1062,7 @@ robj **moduleCreateArgvFromUserFormat(const char *cmdname, const char *fmt, int
  *
  * EINVAL: command non existing, wrong arity, wrong format specifier.
  * EPERM:  operation in Cluster instance with key in non local slot. */
-RedisModuleCallReply *RedisModule_Call(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...) {
+RedisModuleCallReply *RM_Call(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...) {
     struct redisCommand *cmd;
     client *c = NULL;
     robj **argv = NULL;
@@ -1133,7 +1139,7 @@ RedisModuleCallReply *RedisModule_Call(RedisModuleCtx *ctx, const char *cmdname,
         listDelNode(c->reply,listFirst(c->reply));
     }
     reply = moduleCreateCallReplyFromProto(ctx,proto);
-    RedisModule_AutoMemoryAdd(ctx,REDISMODULE_AM_REPLY,reply);
+    RM_AutoMemoryAdd(ctx,REDISMODULE_AM_REPLY,reply);
 
 cleanup:
     freeClient(c);
@@ -1142,7 +1148,7 @@ RedisModuleCallReply *RedisModule_Call(RedisModuleCtx *ctx, const char *cmdname,
 
 /* Return a pointer, and a length, to the protocol returned by the command
  * that returned the reply object. */
-const char *RedisModule_CallReplyProto(RedisModuleCallReply *reply, size_t *len) {
+const char *RM_CallReplyProto(RedisModuleCallReply *reply, size_t *len) {
     if (reply->proto) *len = sdslen(reply->proto);
     return reply->proto;
 }
@@ -1177,7 +1183,7 @@ int moduleRegisterApi(const char *funcname, void *funcptr) {
 }
 
 #define REGISTER_API(name) \
-    moduleRegisterApi("RedisModule_" #name, (void *)(unsigned long)RedisModule_ ## name)
+    moduleRegisterApi("RedisModule_" #name, (void *)(unsigned long)RM_ ## name)
 
 /* Register all the APIs we export. */
 void moduleRegisterCoreAPI(void) {
@@ -1266,7 +1272,7 @@ int moduleLoad(const char *path) {
     void *handle;
     RedisModuleCtx ctx = REDISMODULE_CTX_INIT;
 
-    handle = dlopen(path,RTLD_LAZY);
+    handle = dlopen(path,RTLD_NOW|RTLD_LOCAL);
     if (handle == NULL) return C_ERR;
     onload = (int (*)(void *))(unsigned long) dlsym(handle,"RedisModule_OnLoad");
     if (onload == NULL) {