@@ -752,11 +752,11 @@ RedisModuleString *RM_CreateString(RedisModuleCtx *ctx, const char *ptr, size_t
 }
 
 
-/* Create a new module string object from a printf format and arguments. 
- * The returned string must be freed with RedisModule_FreeString(), unless automatic 
- * memory is enabled.
+/* Create a new module string object from a printf format and arguments.
+ * The returned string must be freed with RedisModule_FreeString(), unless
+ * automatic memory is enabled.
  *
- * The string is created using the sds formatter function sdscatvprintf() */ 
+ * The string is created using the sds formatter function sdscatvprintf(). */
 RedisModuleString *RM_CreateStringPrintf(RedisModuleCtx *ctx, const char *fmt, ...) {
     sds s = sdsempty();
 