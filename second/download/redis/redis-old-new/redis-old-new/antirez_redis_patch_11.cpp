@@ -505,10 +505,10 @@ int RM_IsKeysPositionRequest(RedisModuleCtx *ctx) {
  * RedisModule_IsKeysPositionRequest() API and uses this function in
  * order to report keys, like in the following example:
  *
- *  if (RedisModule_IsKeysPositionRequest(ctx)) {
- *      RedisModule_KeyAtPos(ctx,1);
- *      RedisModule_KeyAtPos(ctx,2);
- *  }
+ *     if (RedisModule_IsKeysPositionRequest(ctx)) {
+ *         RedisModule_KeyAtPos(ctx,1);
+ *         RedisModule_KeyAtPos(ctx,2);
+ *     }
  *
  *  Note: in the example below the get keys API would not be needed since
  *  keys are at fixed positions. This interface is only used for commands
@@ -936,16 +936,16 @@ int RM_StringAppendBuffer(RedisModuleCtx *ctx, RedisModuleString *str, const cha
  * Most functions always return REDISMODULE_OK so you can use it with
  * 'return' in order to return from the command implementation with:
  *
- * if (... some condition ...)
- *     return RM_ReplyWithLongLong(ctx,mycount);
+ *     if (... some condition ...)
+ *         return RM_ReplyWithLongLong(ctx,mycount);
  * -------------------------------------------------------------------------- */
 
 /* Send an error about the number of arguments given to the command,
  * citing the command name in the error message.
  *
  * Example:
  *
- *  if (argc != 3) return RedisModule_WrongArity(ctx);
+ *     if (argc != 3) return RedisModule_WrongArity(ctx);
  */
 int RM_WrongArity(RedisModuleCtx *ctx) {
     addReplyErrorFormat(ctx->client,
@@ -1003,11 +1003,11 @@ int replyWithStatus(RedisModuleCtx *ctx, const char *msg, char *prefix) {
  * the initial error code. The function only provides the initial "-", so
  * the usage is, for example:
  *
- *  RM_ReplyWithError(ctx,"ERR Wrong Type");
+ *     RedisModule_ReplyWithError(ctx,"ERR Wrong Type");
  *
  * and not just:
  *
- *  RM_ReplyWithError(ctx,"Wrong Type");
+ *     RedisModule_ReplyWithError(ctx,"Wrong Type");
  *
  * The function always returns REDISMODULE_OK.
  */
@@ -1062,14 +1062,14 @@ int RM_ReplyWithArray(RedisModuleCtx *ctx, long len) {
  * For example in order to output an array like [1,[10,20,30]] we
  * could write:
  *
- *  RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
- *  RedisModule_ReplyWithLongLong(ctx,1);
- *  RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
- *  RedisModule_ReplyWithLongLong(ctx,10);
- *  RedisModule_ReplyWithLongLong(ctx,20);
- *  RedisModule_ReplyWithLongLong(ctx,30);
- *  RedisModule_ReplySetArrayLength(ctx,3); // Set len of 10,20,30 array.
- *  RedisModule_ReplySetArrayLength(ctx,2); // Set len of top array
+ *      RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
+ *      RedisModule_ReplyWithLongLong(ctx,1);
+ *      RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
+ *      RedisModule_ReplyWithLongLong(ctx,10);
+ *      RedisModule_ReplyWithLongLong(ctx,20);
+ *      RedisModule_ReplyWithLongLong(ctx,30);
+ *      RedisModule_ReplySetArrayLength(ctx,3); // Set len of 10,20,30 array.
+ *      RedisModule_ReplySetArrayLength(ctx,2); // Set len of top array
  *
  * Note that in the above example there is no reason to postpone the array
  * length, since we produce a fixed number of elements, but in the practice
@@ -1428,8 +1428,8 @@ int RM_StringSet(RedisModuleKey *key, RedisModuleString *str) {
  *
  * The 'mode' is composed by bitwise OR-ing the following flags:
  *
- * REDISMODULE_READ -- Read access
- * REDISMODULE_WRITE -- Write access
+ *     REDISMODULE_READ -- Read access
+ *     REDISMODULE_WRITE -- Write access
  *
  * If the DMA is not requested for writing, the pointer returned should
  * only be accessed in a read-only fashion.
@@ -1587,14 +1587,14 @@ int RM_ZsetAddFlagsFromCoreFlags(int flags) {
  *
  * The input flags are:
  *
- * REDISMODULE_ZADD_XX: Element must already exist. Do nothing otherwise.
- * REDISMODULE_ZADD_NX: Element must not exist. Do nothing otherwise.
+ *     REDISMODULE_ZADD_XX: Element must already exist. Do nothing otherwise.
+ *     REDISMODULE_ZADD_NX: Element must not exist. Do nothing otherwise.
  *
  * The output flags are:
  *
- * REDISMODULE_ZADD_ADDED: The new element was added to the sorted set.
- * REDISMODULE_ZADD_UPDATED: The score of the element was updated.
- * REDISMODULE_ZADD_NOP: No operation was performed because XX or NX flags.
+ *     REDISMODULE_ZADD_ADDED: The new element was added to the sorted set.
+ *     REDISMODULE_ZADD_UPDATED: The score of the element was updated.
+ *     REDISMODULE_ZADD_NOP: No operation was performed because XX or NX flags.
  *
  * On success the function returns REDISMODULE_OK. On the following errors
  * REDISMODULE_ERR is returned:
@@ -2010,25 +2010,25 @@ int RM_ZsetRangePrev(RedisModuleKey *key) {
  *
  * Example to set the hash argv[1] to the value argv[2]:
  *
- *  RedisModule_HashSet(key,REDISMODULE_HASH_NONE,argv[1],argv[2],NULL);
+ *      RedisModule_HashSet(key,REDISMODULE_HASH_NONE,argv[1],argv[2],NULL);
  *
  * The function can also be used in order to delete fields (if they exist)
  * by setting them to the specified value of REDISMODULE_HASH_DELETE:
  *
- *  RedisModule_HashSet(key,REDISMODULE_HASH_NONE,argv[1],
- *                      REDISMODULE_HASH_DELETE,NULL);
+ *      RedisModule_HashSet(key,REDISMODULE_HASH_NONE,argv[1],
+ *                          REDISMODULE_HASH_DELETE,NULL);
  *
  * The behavior of the command changes with the specified flags, that can be
  * set to REDISMODULE_HASH_NONE if no special behavior is needed.
  *
- * REDISMODULE_HASH_NX: The operation is performed only if the field was not
- *                     already existing in the hash.
- * REDISMODULE_HASH_XX: The operation is performed only if the field was
- *                     already existing, so that a new value could be
- *                     associated to an existing filed, but no new fields
- *                     are created.
- * REDISMODULE_HASH_CFIELDS: The field names passed are null terminated C
- *                          strings instead of RedisModuleString objects.
+ *     REDISMODULE_HASH_NX: The operation is performed only if the field was not
+ *                          already existing in the hash.
+ *     REDISMODULE_HASH_XX: The operation is performed only if the field was
+ *                          already existing, so that a new value could be
+ *                          associated to an existing filed, but no new fields
+ *                          are created.
+ *     REDISMODULE_HASH_CFIELDS: The field names passed are null terminated C
+ *                               strings instead of RedisModuleString objects.
  *
  * Unless NX is specified, the command overwrites the old field value with
  * the new one.
@@ -2037,8 +2037,8 @@ int RM_ZsetRangePrev(RedisModuleKey *key) {
  * normal C strings, so for example to delete the field "foo" the following
  * code can be used:
  *
- *  RedisModule_HashSet(key,REDISMODULE_HASH_CFIELDS,"foo",
- *                      REDISMODULE_HASH_DELETE,NULL);
+ *      RedisModule_HashSet(key,REDISMODULE_HASH_CFIELDS,"foo",
+ *                          REDISMODULE_HASH_DELETE,NULL);
  *
  * Return value:
  *
@@ -2417,7 +2417,7 @@ RedisModuleString *RM_CreateStringFromCallReply(RedisModuleCallReply *reply) {
  * The integer pointed by 'flags' is populated with flags according
  * to special modifiers in "fmt". For now only one exists:
  *
- * "!" -> REDISMODULE_ARGV_REPLICATE
+ *     "!" -> REDISMODULE_ARGV_REPLICATE
  *
  * On error (format specifier error) NULL is returned and nothing is
  * allocated. On success the argument vector is returned. */
@@ -2607,7 +2607,7 @@ const char *RM_CallReplyProto(RedisModuleCallReply *reply, size_t *len) {
  *
  * The resulting 64 bit integer is composed as follows:
  *
- * (high order bits) 6|6|6|6|6|6|6|6|6|10 (low order bits)
+ *     (high order bits) 6|6|6|6|6|6|6|6|6|10 (low order bits)
  *
  * The first 6 bits value is the first character, name[0], while the last
  * 6 bits value, immediately before the 10 bits integer, is name[8].
@@ -3098,31 +3098,31 @@ float RM_LoadFloat(RedisModuleIO *io) {
  * To add a sequence of unordered elements (for example in the case of a Redis
  * Set), the pattern to use is:
  *
- * foreach element {
- *     AddElement(element);
- *     EndSequence();
- * }
+ *     foreach element {
+ *         AddElement(element);
+ *         EndSequence();
+ *     }
  *
  * Because Sets are not ordered, so every element added has a position that
  * does not depend from the other. However if instead our elements are
  * ordered in pairs, like field-value pairs of an Hash, then one should
  * use:
  *
- * foreach key,value {
- *     AddElement(key);
- *     AddElement(value);
- *     EndSquence();
- * }
+ *     foreach key,value {
+ *         AddElement(key);
+ *         AddElement(value);
+ *         EndSquence();
+ *     }
  *
  * Because the key and value will be always in the above order, while instead
  * the single key-value pairs, can appear in any position into a Redis hash.
  *
  * A list of ordered elements would be implemented with:
  *
- * foreach element {
- *     AddElement(element);
- * }
- * EndSequence();
+ *     foreach element {
+ *         AddElement(element);
+ *     }
+ *     EndSequence();
  *
  */
 void RM_DigestAddStringBuffer(RedisModuleDigest *md, unsigned char *ele, size_t len) {
@@ -3218,8 +3218,8 @@ RedisModuleCtx *RM_GetContextFromIO(RedisModuleIO *io) {
 
 /* This is the low level function implementing both:
  *
- *  RM_Log()
- *  RM_LogIOError()
+ *      RM_Log()
+ *      RM_LogIOError()
  *
  */
 void RM_LogRaw(RedisModule *module, const char *levelstr, const char *fmt, va_list ap) {
@@ -3238,8 +3238,7 @@ void RM_LogRaw(RedisModule *module, const char *levelstr, const char *fmt, va_li
     serverLogRaw(level,msg);
 }
 
-/*
- * Produces a log message to the standard Redis log, the format accepts
+/* Produces a log message to the standard Redis log, the format accepts
  * printf-alike specifiers, while level is a string describing the log
  * level to use when emitting the log, and must be one of the following:
  *
@@ -3318,12 +3317,14 @@ void unblockClientFromModule(client *c) {
  *
  * The callbacks are called in the following contexts:
  *
- * reply_callback:  called after a successful RedisModule_UnblockClient() call
- *                  in order to reply to the client and unblock it.
- * reply_timeout:   called when the timeout is reached in order to send an
- *                  error to the client.
- * free_privdata:   called in order to free the privata data that is passed
- *                  by RedisModule_UnblockClient() call.
+ *     reply_callback:  called after a successful RedisModule_UnblockClient()
+ *                      call in order to reply to the client and unblock it.
+ *
+ *     reply_timeout:   called when the timeout is reached in order to send an
+ *                      error to the client.
+ *
+ *     free_privdata:   called in order to free the privata data that is passed
+ *                      by RedisModule_UnblockClient() call.
  */
 RedisModuleBlockedClient *RM_BlockClient(RedisModuleCtx *ctx, RedisModuleCmdFunc reply_callback, RedisModuleCmdFunc timeout_callback, void (*free_privdata)(void*), long long timeout_ms) {
     client *c = ctx->client;
@@ -3499,9 +3500,9 @@ void *RM_GetBlockedClientPrivateData(RedisModuleCtx *ctx) {
  *
  * To call non-reply APIs, the thread safe context must be prepared with:
  *
- *  RedisModule_ThreadSafeCallStart(ctx);
- *  ... make your call here ...
- *  RedisModule_ThreadSafeCallStop(ctx);
+ *     RedisModule_ThreadSafeCallStart(ctx);
+ *     ... make your call here ...
+ *     RedisModule_ThreadSafeCallStop(ctx);
  *
  * This is not needed when using `RedisModule_Reply*` functions, assuming
  * that a blocked client was used when the context was created, otherwise
@@ -3683,8 +3684,8 @@ int moduleLoad(const char *path, void **module_argv, int module_argc) {
  * C_OK is returned, otherwise C_ERR is returned and errno is set
  * to the following values depending on the type of error:
  *
- * ENONET: No such module having the specified name.
- * EBUSY: The module exports a new data type and can only be reloaded. */
+ * * ENONET: No such module having the specified name.
+ * * EBUSY: The module exports a new data type and can only be reloaded. */
 int moduleUnload(sds name) {
     struct RedisModule *module = dictFetchValue(modules,name);
 