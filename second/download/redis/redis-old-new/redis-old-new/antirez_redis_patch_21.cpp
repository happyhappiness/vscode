@@ -2705,11 +2705,13 @@ moduleType *moduleTypeLookupModuleByID(uint64_t id) {
 }
 
 /* Turn an (unresolved) module ID into a type name, to show the user an
- * error when RDB files contain module data we can't load. */
+ * error when RDB files contain module data we can't load.
+ * The buffer pointed by 'name' must be 10 bytes at least. The function will
+ * fill it with a null terminated module name. */
 void moduleTypeNameByID(char *name, uint64_t moduleid) {
     const char *cset = ModuleTypeNameCharSet;
 
-    name[0] = '\0';
+    name[9] = '\0';
     char *p = name+8;
     moduleid >>= 10;
     for (int j = 0; j < 9; j++) {
@@ -2877,7 +2879,8 @@ void moduleRDBLoadError(RedisModuleIO *io) {
  * data types. */
 void RM_SaveUnsigned(RedisModuleIO *io, uint64_t value) {
     if (io->error) return;
-    int retval = rdbSaveLen(io->rio, value);
+    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_UINT);
+    if (retval != -1) rdbSaveLen(io->rio, value);
     if (retval == -1) {
         io->error = 1;
     } else {
@@ -2889,13 +2892,18 @@ void RM_SaveUnsigned(RedisModuleIO *io, uint64_t value) {
  * be called in the context of the rdb_load method of modules implementing
  * new data types. */
 uint64_t RM_LoadUnsigned(RedisModuleIO *io) {
+    if (io->ver == 2) {
+        uint64_t opcode = rdbLoadLen(io->rio,NULL);
+        if (opcode != RDB_MODULE_OPCODE_UINT) goto loaderr;
+    }
     uint64_t value;
     int retval = rdbLoadLenByRef(io->rio, NULL, &value);
-    if (retval == -1) {
-        moduleRDBLoadError(io);
-        return 0; /* Never reached. */
-    }
+    if (retval == -1) goto loaderr;
     return value;
+
+loaderr:
+    moduleRDBLoadError(io);
+    return 0; /* Never reached. */
 }
 
 /* Like RedisModule_SaveUnsigned() but for signed 64 bit values. */
@@ -2920,7 +2928,8 @@ int64_t RM_LoadSigned(RedisModuleIO *io) {
  * the RDB file. */
 void RM_SaveString(RedisModuleIO *io, RedisModuleString *s) {
     if (io->error) return;
-    int retval = rdbSaveStringObject(io->rio,s);
+    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_STRING);
+    if (retval != -1) retval = rdbSaveStringObject(io->rio,s);
     if (retval == -1) {
         io->error = 1;
     } else {
@@ -2932,7 +2941,8 @@ void RM_SaveString(RedisModuleIO *io, RedisModuleString *s) {
  * as input. */
 void RM_SaveStringBuffer(RedisModuleIO *io, const char *str, size_t len) {
     if (io->error) return;
-    int retval = rdbSaveRawString(io->rio,(unsigned char*)str,len);
+    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_STRING);
+    if (retval != -1) retval = rdbSaveRawString(io->rio,(unsigned char*)str,len);
     if (retval == -1) {
         io->error = 1;
     } else {
@@ -2942,13 +2952,18 @@ void RM_SaveStringBuffer(RedisModuleIO *io, const char *str, size_t len) {
 
 /* Implements RM_LoadString() and RM_LoadStringBuffer() */
 void *moduleLoadString(RedisModuleIO *io, int plain, size_t *lenptr) {
+    if (io->ver == 2) {
+        uint64_t opcode = rdbLoadLen(io->rio,NULL);
+        if (opcode != RDB_MODULE_OPCODE_STRING) goto loaderr;
+    }
     void *s = rdbGenericLoadStringObject(io->rio,
               plain ? RDB_LOAD_PLAIN : RDB_LOAD_NONE, lenptr);
-    if (s == NULL) {
-        moduleRDBLoadError(io);
-        return NULL; /* Never reached. */
-    }
+    if (s == NULL) goto loaderr;
     return s;
+
+loaderr:
+    moduleRDBLoadError(io);
+    return NULL; /* Never reached. */
 }
 
 /* In the context of the rdb_load method of a module data type, loads a string
@@ -2980,7 +2995,8 @@ char *RM_LoadStringBuffer(RedisModuleIO *io, size_t *lenptr) {
  * It is possible to load back the value with RedisModule_LoadDouble(). */
 void RM_SaveDouble(RedisModuleIO *io, double value) {
     if (io->error) return;
-    int retval = rdbSaveBinaryDoubleValue(io->rio, value);
+    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_DOUBLE);
+    if (retval != -1) retval = rdbSaveBinaryDoubleValue(io->rio, value);
     if (retval == -1) {
         io->error = 1;
     } else {
@@ -2991,21 +3007,27 @@ void RM_SaveDouble(RedisModuleIO *io, double value) {
 /* In the context of the rdb_save method of a module data type, loads back the
  * double value saved by RedisModule_SaveDouble(). */
 double RM_LoadDouble(RedisModuleIO *io) {
+    if (io->ver == 2) {
+        uint64_t opcode = rdbLoadLen(io->rio,NULL);
+        if (opcode != RDB_MODULE_OPCODE_DOUBLE) goto loaderr;
+    }
     double value;
     int retval = rdbLoadBinaryDoubleValue(io->rio, &value);
-    if (retval == -1) {
-        moduleRDBLoadError(io);
-        return 0; /* Never reached. */
-    }
+    if (retval == -1) goto loaderr;
     return value;
+
+loaderr:
+    moduleRDBLoadError(io);
+    return 0; /* Never reached. */
 }
 
-/* In the context of the rdb_save method of a module data type, saves a float 
+/* In the context of the rdb_save method of a module data type, saves a float
  * value to the RDB file. The float can be a valid number, a NaN or infinity.
  * It is possible to load back the value with RedisModule_LoadFloat(). */
 void RM_SaveFloat(RedisModuleIO *io, float value) {
     if (io->error) return;
-    int retval = rdbSaveBinaryFloatValue(io->rio, value);
+    int retval = rdbSaveLen(io->rio, RDB_MODULE_OPCODE_FLOAT);
+    if (retval != -1) retval = rdbSaveBinaryFloatValue(io->rio, value);
     if (retval == -1) {
         io->error = 1;
     } else {
@@ -3016,13 +3038,18 @@ void RM_SaveFloat(RedisModuleIO *io, float value) {
 /* In the context of the rdb_save method of a module data type, loads back the
  * float value saved by RedisModule_SaveFloat(). */
 float RM_LoadFloat(RedisModuleIO *io) {
+    if (io->ver == 2) {
+        uint64_t opcode = rdbLoadLen(io->rio,NULL);
+        if (opcode != RDB_MODULE_OPCODE_FLOAT) goto loaderr;
+    }
     float value;
     int retval = rdbLoadBinaryFloatValue(io->rio, &value);
-    if (retval == -1) {
-        moduleRDBLoadError(io);
-        return 0; /* Never reached. */
-    }
+    if (retval == -1) goto loaderr;
     return value;
+
+loaderr:
+    moduleRDBLoadError(io);
+    return 0; /* Never reached. */
 }
 
 /* --------------------------------------------------------------------------