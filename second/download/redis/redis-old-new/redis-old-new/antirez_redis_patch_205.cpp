@@ -2769,6 +2769,30 @@ void RM_EmitAOF(RedisModuleIO *io, const char *cmdname, const char *fmt, ...) {
 }
 
 /* --------------------------------------------------------------------------
+ * Logging
+ * -------------------------------------------------------------------------- */
+
+/* Produces a log message to the standard Redis log. */
+void RM_Log(RedisModuleCtx *ctx, int level, const char *fmt, ...)
+{
+    va_list ap;
+    char msg[LOG_MAX_LEN];
+    size_t name_len;
+
+    if ((level&0xff) < server.verbosity) return;
+    if (!ctx->module) return;   /* Can only log if module is initialized */
+
+    name_len = snprintf(msg, sizeof(msg),"%s: ", ctx->module->name);
+
+    va_start(ap, fmt);
+    vsnprintf(msg + name_len, sizeof(msg) - name_len, fmt, ap);
+    va_end(ap);
+
+    serverLogRaw(level,msg);
+}
+
+
+/* --------------------------------------------------------------------------
  * Modules API internals
  * -------------------------------------------------------------------------- */
 
@@ -2886,6 +2910,7 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(SaveDouble);
     REGISTER_API(LoadDouble);
     REGISTER_API(EmitAOF);
+    REGISTER_API(Log);
 }
 
 /* Global initialization at Redis startup. */