@@ -2849,6 +2849,31 @@ double RM_LoadDouble(RedisModuleIO *io) {
     return value;
 }
 
+/* In the context of the rdb_save method of a module data type, saves a float 
+ * value to the RDB file. The float can be a valid number, a NaN or infinity.
+ * It is possible to load back the value with RedisModule_LoadFloat(). */
+void RM_SaveFloat(RedisModuleIO *io, float value) {
+    if (io->error) return;
+    int retval = rdbSaveBinaryFloatValue(io->rio, value);
+    if (retval == -1) {
+        io->error = 1;
+    } else {
+        io->bytes += retval;
+    }
+}
+
+/* In the context of the rdb_save method of a module data type, loads back the
+ * float value saved by RedisModule_SaveFloat(). */
+float RM_LoadFloat(RedisModuleIO *io) {
+    float value;
+    int retval = rdbLoadBinaryFloatValue(io->rio, &value);
+    if (retval == -1) {
+        moduleRDBLoadError(io);
+        return 0; /* Never reached. */
+    }
+    return value;
+}
+
 /* --------------------------------------------------------------------------
  * AOF API for modules data types
  * -------------------------------------------------------------------------- */
@@ -3280,6 +3305,8 @@ void moduleRegisterCoreAPI(void) {
     REGISTER_API(LoadStringBuffer);
     REGISTER_API(SaveDouble);
     REGISTER_API(LoadDouble);
+    REGISTER_API(SaveFloat);
+    REGISTER_API(LoadFloat);
     REGISTER_API(EmitAOF);
     REGISTER_API(Log);
     REGISTER_API(LogIOError);