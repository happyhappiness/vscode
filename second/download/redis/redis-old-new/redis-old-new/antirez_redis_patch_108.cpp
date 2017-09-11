@@ -2908,7 +2908,30 @@ void RM_EmitAOF(RedisModuleIO *io, const char *cmdname, const char *fmt, ...) {
  * Logging
  * -------------------------------------------------------------------------- */
 
-/* Produces a log message to the standard Redis log, the format accepts
+/* This is the low level function implementing both:
+ *
+ *  RM_Log()
+ *  RM_LogIOError()
+ *
+ */
+void RM_LogRaw(RedisModule *module, const char *levelstr, const char *fmt, va_list ap) {
+    char msg[LOG_MAX_LEN];
+    size_t name_len;
+    int level;
+
+    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
+    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
+    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
+    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
+    else level = LL_VERBOSE; /* Default. */
+
+    name_len = snprintf(msg, sizeof(msg),"<%s> ", module->name);
+    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
+    serverLogRaw(level,msg);
+}
+
+/*
+ * Produces a log message to the standard Redis log, the format accepts
  * printf-alike specifiers, while level is a string describing the log
  * level to use when emitting the log, and must be one of the following:
  *
@@ -2923,26 +2946,24 @@ void RM_EmitAOF(RedisModuleIO *io, const char *cmdname, const char *fmt, ...) {
  * a few lines of text.
  */
 void RM_Log(RedisModuleCtx *ctx, const char *levelstr, const char *fmt, ...) {
-    va_list ap;
-    char msg[LOG_MAX_LEN];
-    size_t name_len;
-    int level;
-
     if (!ctx->module) return;   /* Can only log if module is initialized */
 
-    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
-    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
-    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
-    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
-    else level = LL_VERBOSE; /* Default. */
-
-    name_len = snprintf(msg, sizeof(msg),"<%s> ", ctx->module->name);
-
+    va_list ap;
     va_start(ap, fmt);
-    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
+    RM_LogRaw(ctx->module,levelstr,fmt,ap);
     va_end(ap);
+}
 
-    serverLogRaw(level,msg);
+/* Log errors from RDB / AOF serialization callbacks.
+ *
+ * This function should be used when a callback is returning a critical
+ * error to the caller since cannot load or save the data for some
+ * critical reason. */
+void RM_LogIOError(RedisModuleIO *io, const char *levelstr, const char *fmt, ...) {
+    va_list ap;
+    va_start(ap, fmt);
+    RM_LogRaw(io->type->module,levelstr,fmt,ap);
+    va_end(ap);
 }
 
 /* --------------------------------------------------------------------------
@@ -3261,6 +3282,7 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(LoadDouble);
     REGISTER_API(EmitAOF);
     REGISTER_API(Log);
+    REGISTER_API(LogIOError);
     REGISTER_API(StringAppendBuffer);
     REGISTER_API(RetainString);
     REGISTER_API(StringCompare);