@@ -116,7 +116,7 @@ typedef struct RedisModuleCallReply RedisModuleCallReply;
 
 void RM_FreeCallReply(RedisModuleCallReply *reply);
 void RM_CloseKey(RedisModuleKey *key);
-void RM_AutoMemoryCollect(RedisModuleCtx *ctx);
+void autoMemoryCollect(RedisModuleCtx *ctx);
 robj **moduleCreateArgvFromUserFormat(const char *cmdname, const char *fmt, int *argcp, int *flags, va_list ap);
 void moduleReplicateMultiIfNeeded(RedisModuleCtx *ctx);
 void RM_ZsetRangeStop(RedisModuleKey *key);
@@ -204,7 +204,10 @@ int moduleDelKeyIfEmpty(RedisModuleKey *key) {
 
 /* Lookup the requested module API and store the function pointer into the
  * target pointer. The function returns REDISMODULE_ERR if there is no such
- * named API, otherwise REDISMODULE_OK. */
+ * named API, otherwise REDISMODULE_OK.
+ *
+ * This function is not meant to be used by modules developer, it is only
+ * used implicitly by including redismodule.h. */
 int RM_GetApi(const char *funcname, void **targetPtrPtr) {
     dictEntry *he = dictFind(server.moduleapi, funcname);
     if (!he) return REDISMODULE_ERR;
@@ -221,7 +224,7 @@ void RedisModuleCommandDispatcher(client *c) {
     ctx.module = cp->module;
     ctx.client = c;
     cp->func(&ctx,(void**)c->argv,c->argc);
-    RM_AutoMemoryCollect(&ctx);
+    autoMemoryCollect(&ctx);
     preventCommandPropagation(c);
 
     /* Handle the replication of the final EXEC, since whatever a command
@@ -238,7 +241,18 @@ void RedisModuleCommandDispatcher(client *c) {
 /* Register a new command in the Redis server, that will be handled by
  * calling the function pointer 'func' using the RedisModule calling
  * convention. The function returns REDISMODULE_ERR if the specified command
- * name is already busy, otherwise REDISMODULE_OK. */
+ * name is already busy, otherwise REDISMODULE_OK is returned.
+ *
+ * This function must be called during the initialization of the module
+ * inside the RedisModule_OnLoad() function. Calling this function outside
+ * of the initialization function is not defined.
+ *
+ * The command function type is the following:
+ *
+ *  int MyCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);
+ *
+ * And is supposed to always return REDISMODULE_OK.
+ */
 int RM_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModuleCmdFunc cmdfunc) {
     struct redisCommand *rediscmd;
     RedisModuleCommandProxy *cp;
@@ -252,7 +266,7 @@ int RM_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModuleCmdFunc c
 
     /* Create a command "proxy", which is a structure that is referenced
      * in the command table, so that the generic command that works as
-     * binidng between modules and Redis, can know what function to call
+     * binding between modules and Redis, can know what function to call
      * and what the module is.
      *
      * Note that we use the Redis command table 'getkeys_proc' in order to
@@ -276,7 +290,10 @@ int RM_CreateCommand(RedisModuleCtx *ctx, const char *name, RedisModuleCmdFunc c
     return REDISMODULE_OK;
 }
 
-/* Called by RM_Init() to setup the ctx->module structure. */
+/* Called by RM_Init() to setup the ctx->module structure.
+ *
+ * This is an internal function, Redis modules developers don't need
+ * to use it. */
 void RM_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver, int apiver){
     RedisModule *module;
 
@@ -292,13 +309,16 @@ void RM_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver, int api
  * Automatic memory management for modules
  * -------------------------------------------------------------------------- */
 
-/* Enable auto memory. */
+/* Enable automatic memory management. See API.md for more information.
+ *
+ * The function must be called as the first function of a command implementation
+ * that wants to use automatic memory. */
 void RM_AutoMemory(RedisModuleCtx *ctx) {
     ctx->flags |= REDISMODULE_CTX_AUTO_MEMORY;
 }
 
 /* Add a new object to release automatically when the callback returns. */
-void RM_AutoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
+void autoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
     if (ctx->amqueue_used == ctx->amqueue_len) {
         ctx->amqueue_len *= 2;
@@ -312,7 +332,7 @@ void RM_AutoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
 
 /* Mark an object as freed in the auto release queue, so that users can still
  * free things manually if they want. */
-void RM_AutoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
+void autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
 
     int j;
@@ -329,7 +349,7 @@ void RM_AutoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
 }
 
 /* Release all the objects in queue. */
-void RM_AutoMemoryCollect(RedisModuleCtx *ctx) {
+void autoMemoryCollect(RedisModuleCtx *ctx) {
     if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
     /* Clear the AUTO_MEMORY flag from the context, otherwise the functions
      * we call to free the resources, will try to scan the auto release
@@ -355,37 +375,49 @@ void RM_AutoMemoryCollect(RedisModuleCtx *ctx) {
  * String objects APIs
  * -------------------------------------------------------------------------- */
 
-/* Create a new module string object. Must be freed with
- * RM_FreeString(), unless automatic memory is enabled. */
+/* Create a new module string object. The returned string must be freed
+ * with RedisModule_FreeString(), unless automatic memory is enabled.
+ *
+ * The string is created by copying the `len` bytes starting
+ * at `ptr`. No reference is retained to the passed buffer. */
 RedisModuleString *RM_CreateString(RedisModuleCtx *ctx, const char *ptr, size_t len)
 {
     RedisModuleString *o = createStringObject(ptr,len);
-    RM_AutoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
+    autoMemoryAdd(ctx,REDISMODULE_AM_STRING,o);
     return o;
 }
 
-/* Like RM_CreatString, but creates a string starting from a long long
- * integer instea of taking a buffer and length. */
+/* Like RedisModule_CreatString(), but creates a string starting from a long long
+ * integer instead of taking a buffer and its length.
+ *
+ * The returned string must be released with RedisModule_FreeString() or by
+ * enabling automatic memory management. */
 RedisModuleString *RM_CreateStringFromLongLong(RedisModuleCtx *ctx, long long ll) {
     char buf[LONG_STR_SIZE];
     size_t len = ll2string(buf,sizeof(buf),ll);
     return RM_CreateString(ctx,buf,len);
 }
 
-/* Free a module string object obtained with one of the Redis API calls
- * that return new string objects. */
+/* Free a module string object obtained with one of the Redis modules API calls
+ * that return new string objects.
+ *
+ * It is possible to call this function even when automatic memory management
+ * is enabled. In that case the string will be released ASAP and removed
+ * from the pool of string to release at the end. */
 void RM_FreeString(RedisModuleCtx *ctx, RedisModuleString *str) {
     decrRefCount(str);
-    RM_AutoMemoryFreed(ctx,REDISMODULE_AM_STRING,str);
+    autoMemoryFreed(ctx,REDISMODULE_AM_STRING,str);
 }
 
-/* Return the string pointer and length. */
+/* Given a string module object, this function returns the string pointer
+ * and length of the string. The returned pointer and length should only
+ * be used for read only accesses and never modified. */
 const char *RM_StringPtrLen(RedisModuleString *str, size_t *len) {
     if (len) *len = sdslen(str->ptr);
     return str->ptr;
 }
 
-/* Turn the string into a long long, storing it at *ll.
+/* Convert the string into a long long integer, storing it at *ll.
  * Returns REDISMODULE_OK on success. If the string can't be parsed
  * as a valid, strict long long (no spaces before/after), REDISMODULE_ERR
  * is returned. */
@@ -394,7 +426,7 @@ int RM_StringToLongLong(RedisModuleString *str, long long *ll) {
                                                      REDISMODULE_ERR;
 }
 
-/* Turn the string into a double, storing it at *d.
+/* Convert the string into a double, storing it at *d.
  * Returns REDISMODULE_OK on success or REDISMODULE_ERR if the string is
  * not a valid string representation of a double value. */
 int RM_StringToDouble(RedisModuleString *str, double *d) {
@@ -412,24 +444,31 @@ int RM_StringToDouble(RedisModuleString *str, double *d) {
  *     return RM_ReplyWithLongLong(ctx,mycount);
  * -------------------------------------------------------------------------- */
 
-/* Send an error about the number of arguments given to the command. */
+/* Send an error about the number of arguments given to the command,
+ * citing the command name in the error message.
+ *
+ * Example:
+ *
+ *  if (argc != 3) return RedisModule_WrongArity(ctx);
+ */
 int RM_WrongArity(RedisModuleCtx *ctx) {
     addReplyErrorFormat(ctx->client,
         "wrong number of arguments for '%s' command",
         (char*)ctx->client->argv[0]->ptr);
     return REDISMODULE_OK;
 }
 
-/* Send an integer reply with the specified long long value.
+/* Send an integer reply to the client, with the specified long long value.
  * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithLongLong(RedisModuleCtx *ctx, long long ll) {
     addReplyLongLong(ctx->client,ll);
     return REDISMODULE_OK;
 }
 
 /* Reply with an error or simple string (status message). Used to implement
- * ReplyWithSimpleString() and ReplyWithError(). */
-int RM_ReplyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
+ * ReplyWithSimpleString() and ReplyWithError().
+ * The function always returns REDISMODULE_OK. */
+int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
     sds strmsg = sdsnewlen(prefix,1);
     strmsg = sdscat(strmsg,msg);
     strmsg = sdscatlen(strmsg,"\r\n",2);
@@ -443,57 +482,80 @@ int RM_ReplyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
  * the initial error code. The function only provides the initial "-", so
  * the usage is, for example:
  *
- * RM_ReplyWithError(ctx,"ERR Wrong Type");
+ *  RM_ReplyWithError(ctx,"ERR Wrong Type");
  *
  * and not just:
  *
- * RM_ReplyWithError(ctx,"Wrong Type");
+ *  RM_ReplyWithError(ctx,"Wrong Type");
+ *
+ * The function always returns REDISMODULE_OK.
  */
 int RM_ReplyWithError(RedisModuleCtx *ctx, const char *err) {
-    return RM_ReplyWithStatus(ctx,err,"-");
+    return replyWithStatus(ctx,err,"-");
 }
 
 /* Reply with a simple string (+... \r\n in RESP protocol). This replies
- * are suitalbe only when sending a small non-binary string wiht small
- * overhead, like "OK" or similar replies. */
+ * are suitable only when sending a small non-binary string with small
+ * overhead, like "OK" or similar replies.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithSimpleString(RedisModuleCtx *ctx, const char *msg) {
-    return RM_ReplyWithStatus(ctx,msg,"+");
+    return replyWithStatus(ctx,msg,"+");
 }
 
 /* Reply with an array type of 'len' elements. However 'len' other calls
  * to ReplyWith* style functions must follow in order to emit the elements
- * of the array. */
+ * of the array.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithArray(RedisModuleCtx *ctx, int len) {
     addReplyMultiBulkLen(ctx->client,len);
     return REDISMODULE_OK;
 }
 
-/* Reply with a bulk string, taking in input a C buffer pointer and length. */
+/* Reply with a bulk string, taking in input a C buffer pointer and length.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithStringBuffer(RedisModuleCtx *ctx, const char *buf, size_t len) {
     addReplyBulkCBuffer(ctx->client,(char*)buf,len);
     return REDISMODULE_OK;
 }
 
-/* Reply with a bulk string, taking in input a RedisModuleString object. */
+/* Reply with a bulk string, taking in input a RedisModuleString object.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithString(RedisModuleCtx *ctx, RedisModuleString *str) {
     addReplyBulk(ctx->client,str);
     return REDISMODULE_OK;
 }
 
-/* Reply with NULL. */
+/* Reply to the client with a NULL. In the RESP protocol a NULL is encoded
+ * as the string "$-1\r\n".
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithNull(RedisModuleCtx *ctx) {
     addReply(ctx->client,shared.nullbulk);
     return REDISMODULE_OK;
 }
 
-/* Reply exactly what a Redis command returned us with RM_Call(). */
+/* Reply exactly what a Redis command returned us with RedisModule_Call().
+ * This function is useful when we use RedisModule_Call() in order to
+ * execute some command, as we want to reply to the client exactly the
+ * same reply we obtained by the command.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithCallReply(RedisModuleCtx *ctx, RedisModuleCallReply *reply) {
     sds proto = sdsnewlen(reply->proto, reply->protolen);
     addReplySds(ctx->client,proto);
     return REDISMODULE_OK;
 }
 
-/* Send a string reply obtained converting the double 'd' into a string. */
+/* Send a string reply obtained converting the double 'd' into a bulk string.
+ * This function is basically equivalent to converting a double into
+ * a string into a C buffer, and then calling the function
+ * RedisModule_ReplyWithStringBuffer() with the buffer and length.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplyWithDouble(RedisModuleCtx *ctx, double d) {
     addReplyDouble(ctx->client,d);
     return REDISMODULE_OK;
@@ -515,13 +577,22 @@ void moduleReplicateMultiIfNeeded(RedisModuleCtx *ctx) {
 /* Replicate the specified command and arguments to slaves and AOF, as effect
  * of execution of the calling command implementation.
  *
- * The replicated commands are always wrapepd into the MULTI/EXEC that
+ * The replicated commands are always wrapped into the MULTI/EXEC that
  * contains all the commands replicated in a given module command
- * execution. However the commands replicated with RM_Call()
- * are the first items, the ones replicated with RM_Replicate()
+ * execution. However the commands replicated with RedisModule_Call()
+ * are the first items, the ones replicated with RedisModule_Replicate()
  * will all follow before the EXEC.
  *
- * Modules should try to use one interface or the other. */
+ * Modules should try to use one interface or the other.
+ *
+ * This command follows exactly the same interface of RedisModule_Call(),
+ * so a set of format specifiers must be passed, followed by arguments
+ * matching the provided format specifiers.
+ *
+ * Please refer to RedisModule_Call() for more information.
+ *
+ * The command returns REDISMODULE_ERR if the format specifiers are invalid
+ * or the command name does not belong to a known command. */
 int RM_Replicate(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...) {
     struct redisCommand *cmd;
     robj **argv = NULL;
@@ -549,9 +620,16 @@ int RM_Replicate(RedisModuleCtx *ctx, const char *cmdname, const char *fmt, ...)
 }
 
 /* This function will replicate the command exactly as it was invoked
- * by the client. This function will not wrap the command into
+ * by the client. Note that this function will not wrap the command into
  * a MULTI/EXEC stanza, so it should not be mixed with other replication
- * commands. */
+ * commands.
+ *
+ * Basically this form of replication is useful when you want to propagate
+ * the command to the slaves and AOF file exactly as it was called, since
+ * the command can just be re-executed to deterministically re-create the
+ * new state starting from the old one.
+ *
+ * The function always returns REDISMODULE_OK. */
 int RM_ReplicateVerbatim(RedisModuleCtx *ctx) {
     alsoPropagate(ctx->client->cmd,ctx->client->db->id,
         ctx->client->argv,ctx->client->argc,
@@ -569,7 +647,15 @@ int RM_GetSelectedDb(RedisModuleCtx *ctx) {
 }
 
 /* Change the currently selected DB. Returns an error if the id
- * is out of range. */
+ * is out of range.
+ *
+ * Note that the client will retain the currently selected DB even after
+ * the Redis command implemented by the module calling this function
+ * returns.
+ *
+ * If the module command wishes to change something in a different DB and
+ * returns back to the original one, it should call RedisModule_GetSelectedDb()
+ * before in order to restore the old DB number before returning. */
 int RM_SelectDb(RedisModuleCtx *ctx, int newid) {
     int retval = selectDb(ctx->client,newid);
     return (retval == C_OK) ? REDISMODULE_OK : REDISMODULE_ERR;
@@ -587,7 +673,7 @@ int RM_SelectDb(RedisModuleCtx *ctx, int newid) {
  * a yet not existing key (that will be created, for example, after
  * a list push operation). If the mode is just READ instead, and the
  * key does not exist, NULL is returned. However it is still safe to
- * call RM_CloseKey() and RM_KeyType() on a NULL
+ * call RedisModule_CloseKey() and RedisModule_KeyType() on a NULL
  * value. */
 void *RM_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
     RedisModuleKey *kp;
@@ -612,7 +698,7 @@ void *RM_OpenKey(RedisModuleCtx *ctx, robj *keyname, int mode) {
     kp->iter = NULL;
     kp->mode = mode;
     RM_ZsetRangeStop(kp);
-    RM_AutoMemoryAdd(ctx,REDISMODULE_AM_KEY,kp);
+    autoMemoryAdd(ctx,REDISMODULE_AM_KEY,kp);
     return (void*)kp;
 }
 
@@ -622,7 +708,7 @@ void RM_CloseKey(RedisModuleKey *key) {
     if (key->mode & REDISMODULE_WRITE) signalModifiedKey(key->db,key->key);
     /* TODO: if (key->iter) RM_KeyIteratorStop(kp); */
     decrRefCount(key->key);
-    RM_AutoMemoryFreed(key->ctx,REDISMODULE_AM_KEY,key);
+    autoMemoryFreed(key->ctx,REDISMODULE_AM_KEY,key);
     zfree(key);
 }
 
@@ -847,7 +933,7 @@ RedisModuleString *RM_ListPop(RedisModuleKey *key, int where) {
     robj *decoded = getDecodedObject(ele);
     decrRefCount(ele);
     moduleDelKeyIfEmpty(key);
-    RM_AutoMemoryAdd(key->ctx,REDISMODULE_AM_STRING,decoded);
+    autoMemoryAdd(key->ctx,REDISMODULE_AM_STRING,decoded);
     return decoded;
 }
 
@@ -1088,7 +1174,7 @@ RedisModuleString *RM_ZsetRangeCurrentElement(RedisModuleKey *key, double *score
     } else {
         serverPanic("Unsupported zset encoding");
     }
-    RM_AutoMemoryAdd(key->ctx,REDISMODULE_AM_STRING,str);
+    autoMemoryAdd(key->ctx,REDISMODULE_AM_STRING,str);
     return str;
 }
 
@@ -1363,7 +1449,7 @@ void RM_FreeCallReply_Rec(RedisModuleCallReply *reply, int freenested){
  * if called by the module API. */
 void RM_FreeCallReply(RedisModuleCallReply *reply) {
     RM_FreeCallReply_Rec(reply,0);
-    RM_AutoMemoryFreed(reply->ctx,REDISMODULE_AM_REPLY,reply);
+    autoMemoryFreed(reply->ctx,REDISMODULE_AM_REPLY,reply);
 }
 
 /* Return the reply type. */
@@ -1572,7 +1658,7 @@ RedisModuleCallReply *RM_Call(RedisModuleCtx *ctx, const char *cmdname, const ch
         listDelNode(c->reply,listFirst(c->reply));
     }
     reply = moduleCreateCallReplyFromProto(ctx,proto);
-    RM_AutoMemoryAdd(ctx,REDISMODULE_AM_REPLY,reply);
+    autoMemoryAdd(ctx,REDISMODULE_AM_REPLY,reply);
 
 cleanup:
     freeClient(c);