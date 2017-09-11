@@ -2772,17 +2772,35 @@ void RM_EmitAOF(RedisModuleIO *io, const char *cmdname, const char *fmt, ...) {
  * Logging
  * -------------------------------------------------------------------------- */
 
-/* Produces a log message to the standard Redis log. */
-void RM_Log(RedisModuleCtx *ctx, int level, const char *fmt, ...)
-{
+/* Produces a log message to the standard Redis log, the format accepts
+ * printf-alike specifiers, while level is a string describing the log
+ * level to use when emitting the log, and must be one of the following:
+ *
+ * * "debug"
+ * * "verbose"
+ * * "notice"
+ * * "warning"
+ *
+ * If the specified log level is invalid, verbose is used by default.
+ * There is a fixed limit to the length of the log line this function is able
+ * to emit, this limti is not specified but is guaranteed to be more than
+ * a few lines of text.
+ */
+void RM_Log(RedisModuleCtx *ctx, const char *levelstr, const char *fmt, ...) {
     va_list ap;
     char msg[LOG_MAX_LEN];
     size_t name_len;
+    int level;
 
-    if ((level&0xff) < server.verbosity) return;
     if (!ctx->module) return;   /* Can only log if module is initialized */
 
-    name_len = snprintf(msg, sizeof(msg),"%s: ", ctx->module->name);
+    if (!strcasecmp(levelstr,"debug")) level = LL_DEBUG;
+    else if (!strcasecmp(levelstr,"verbose")) level = LL_VERBOSE;
+    else if (!strcasecmp(levelstr,"notice")) level = LL_NOTICE;
+    else if (!strcasecmp(levelstr,"warning")) level = LL_WARNING;
+    else level = LL_VERBOSE; /* Default. */
+
+    name_len = snprintf(msg, sizeof(msg),"<%s> ", ctx->module->name);
 
     va_start(ap, fmt);
     vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
@@ -2791,7 +2809,6 @@ void RM_Log(RedisModuleCtx *ctx, int level, const char *fmt, ...)
     serverLogRaw(level,msg);
 }
 
-
 /* --------------------------------------------------------------------------
  * Modules API internals
  * -------------------------------------------------------------------------- */