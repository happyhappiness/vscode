@@ -615,9 +615,12 @@ void autoMemoryAdd(RedisModuleCtx *ctx, int type, void *ptr) {
 }
 
 /* Mark an object as freed in the auto release queue, so that users can still
- * free things manually if they want. */
-void autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
-    if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return;
+ * free things manually if they want.
+ *
+ * The function returns 1 if the object was actually found in the auto memory
+ * pool, otherwise 0 is returned. */
+int autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
+    if (!(ctx->flags & REDISMODULE_CTX_AUTO_MEMORY)) return 0;
 
     int count = (ctx->amqueue_used+1)/2;
     for (int j = 0; j < count; j++) {
@@ -639,10 +642,11 @@ void autoMemoryFreed(RedisModuleCtx *ctx, int type, void *ptr) {
                 /* Reduce the size of the queue because we either moved the top
                  * element elsewhere or freed it */
                 ctx->amqueue_used--;
-                return;
+                return 1;
             }
         }
     }
+    return 0;
 }
 
 /* Release all the objects in queue. */
@@ -717,6 +721,43 @@ void RM_FreeString(RedisModuleCtx *ctx, RedisModuleString *str) {
     autoMemoryFreed(ctx,REDISMODULE_AM_STRING,str);
 }
 
+/* Every call to this function, will make the string 'str' requiring
+ * an additional call to RedisModule_FreeString() in order to really
+ * free the string. Note that the automatic freeing of the string obtained
+ * enabling modules automatic memory management counts for one
+ * RedisModule_FreeString() call (it is just executed automatically).
+ *
+ * Normally you want to call this function when, at the same time
+ * the following conditions are true:
+ *
+ * 1) You have automatic memory management enabled.
+ * 2) You want to create string objects.
+ * 3) Those string objects you create need to live *after* the callback
+ *    function(for example a command implementation) creating them returns.
+ *
+ * Usually you want this in order to store the created string object
+ * into your own data structure, for example when implementing a new data
+ * type.
+ *
+ * Note that when memory management is turned off, you don't need
+ * any call to RetainString() since creating a string will always result
+ * into a string that lives after the callback function returns, if
+ * no FreeString() call is performed. */
+void RM_RetainString(RedisModuleCtx *ctx, RedisModuleString *str) {
+    if (!autoMemoryFreed(ctx,REDISMODULE_AM_STRING,str)) {
+        /* Increment the string reference counting only if we can't
+         * just remove the object from the list of objects that should
+         * be reclaimed. Why we do that, instead of just incrementing
+         * the refcount in any case, and let the automatic FreeString()
+         * call at the end to bring the refcount back at the desired
+         * value? Because this way we ensure that the object refcount
+         * value is 1 (instead of going to 2 to be dropped later to 1)
+         * after the call to this function. This is needed for functions
+         * like RedisModule_StringAppendBuffer() to work. */
+        incrRefCount(str);
+    }
+}
+
 /* Given a string module object, this function returns the string pointer
  * and length of the string. The returned pointer and length should only
  * be used for read only accesses and never modified. */
@@ -742,6 +783,40 @@ int RM_StringToDouble(const RedisModuleString *str, double *d) {
     return (retval == C_OK) ? REDISMODULE_OK : REDISMODULE_ERR;
 }
 
+/* Return the (possibly modified in encoding) input 'str' object if
+ * the string is unshared, otherwise NULL is returned. */
+RedisModuleString *moduleAssertUnsharedString(RedisModuleString *str) {
+    if (str->refcount != 1) {
+        serverLog(LL_WARNING,
+            "Module attempted to use an in-place string modify operation "
+            "with a string referenced multiple times. Please check the code "
+            "for API usage correctness.");
+        return NULL;
+    }
+    if (str->encoding == OBJ_ENCODING_EMBSTR) {
+        /* Note: here we "leak" the additional allocation that was
+         * used in order to store the embedded string in the object. */
+        str->ptr = sdsnewlen(str->ptr,sdslen(str->ptr));
+        str->encoding = OBJ_ENCODING_RAW;
+    } else if (str->encoding == OBJ_ENCODING_INT) {
+        /* Convert the string from integer to raw encoding. */
+        str->ptr = sdsfromlonglong((long)str->ptr);
+        str->encoding = OBJ_ENCODING_RAW;
+    }
+    return str;
+}
+
+/* Append the specified buffere to the string 'str'. The string must be a
+ * string created by the user that is referenced only a single time, otherwise
+ * REDISMODULE_ERR is returend and the operation is not performed. */
+int RM_StringAppendBuffer(RedisModuleCtx *ctx, RedisModuleString *str, const char *buf, size_t len) {
+    UNUSED(ctx);
+    str = moduleAssertUnsharedString(str);
+    if (str == NULL) return REDISMODULE_ERR;
+    str->ptr = sdscatlen(str->ptr,buf,len);
+    return REDISMODULE_OK;
+}
+
 /* --------------------------------------------------------------------------
  * Reply APIs
  *
@@ -2954,6 +3029,8 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(LoadDouble);
     REGISTER_API(EmitAOF);
     REGISTER_API(Log);
+    REGISTER_API(StringAppendBuffer);
+    REGISTER_API(RetainString);
 }
 
 /* Global initialization at Redis startup. */