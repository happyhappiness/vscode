@@ -623,7 +623,7 @@ int rdbSaveObjectType(rio *rdb, robj *o) {
         else
             serverPanic("Unknown hash encoding");
     case OBJ_MODULE:
-        return rdbSaveType(rdb,RDB_TYPE_MODULE);
+        return rdbSaveType(rdb,RDB_TYPE_MODULE_2);
     default:
         serverPanic("Unknown object type");
     }
@@ -775,8 +775,12 @@ ssize_t rdbSaveObject(rio *rdb, robj *o) {
         if (retval == -1) return -1;
         io.bytes += retval;
 
-        /* Then write the module-specific representation. */
+        /* Then write the module-specific representation + EOF marker. */
         mt->rdb_save(&io,mv->value);
+        retval = rdbSaveLen(rdb,RDB_MODULE_OPCODE_EOF);
+        if (retval == -1) return -1;
+        io.bytes += retval;
+
         if (io.ctx) {
             moduleFreeContext(io.ctx);
             zfree(io.ctx);
@@ -1102,6 +1106,45 @@ void rdbRemoveTempFile(pid_t childpid) {
     unlink(tmpfile);
 }
 
+/* This function is called by rdbLoadObject() when the code is in RDB-check
+ * mode and we find a module value of type 2 that can be parsed without
+ * the need of the actual module. The value is parsed for errors, finally
+ * a dummy redis object is returned just to conform to the API. */
+robj *rdbLoadCheckModuleValue(rio *rdb, char *modulename) {
+    uint64_t opcode;
+    while((opcode = rdbLoadLen(rdb,NULL)) != RDB_MODULE_OPCODE_EOF) {
+        if (opcode == RDB_MODULE_OPCODE_SINT ||
+            opcode == RDB_MODULE_OPCODE_UINT)
+        {
+            uint64_t len;
+            if (rdbLoadLenByRef(rdb,NULL,&len) == -1) {
+                rdbExitReportCorruptRDB(
+                    "Error reading integer from module %s value", modulename);
+            }
+        } else if (opcode == RDB_MODULE_OPCODE_STRING) {
+            robj *o = rdbGenericLoadStringObject(rdb,RDB_LOAD_NONE,NULL);
+            if (o == NULL) {
+                rdbExitReportCorruptRDB(
+                    "Error reading string from module %s value", modulename);
+            }
+            decrRefCount(o);
+        } else if (opcode == RDB_MODULE_OPCODE_FLOAT) {
+            float val;
+            if (rdbLoadBinaryFloatValue(rdb,&val) == -1) {
+                rdbExitReportCorruptRDB(
+                    "Error reading float from module %s value", modulename);
+            }
+        } else if (opcode == RDB_MODULE_OPCODE_DOUBLE) {
+            double val;
+            if (rdbLoadBinaryDoubleValue(rdb,&val) == -1) {
+                rdbExitReportCorruptRDB(
+                    "Error reading double from module %s value", modulename);
+            }
+        }
+    }
+    return createStringObject("module-dummy-value",18);
+}
+
 /* Load a Redis object of the specified type from the specified file.
  * On success a newly allocated object is returned, otherwise NULL. */
 robj *rdbLoadObject(int rdbtype, rio *rdb) {
@@ -1353,21 +1396,35 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
                 rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
                 break;
         }
-    } else if (rdbtype == RDB_TYPE_MODULE) {
+    } else if (rdbtype == RDB_TYPE_MODULE || rdbtype == RDB_TYPE_MODULE_2) {
         uint64_t moduleid = rdbLoadLen(rdb,NULL);
         moduleType *mt = moduleTypeLookupModuleByID(moduleid);
         char name[10];
 
+        if (rdbCheckMode && rdbtype == RDB_TYPE_MODULE_2)
+            return rdbLoadCheckModuleValue(rdb,name);
+
         if (mt == NULL) {
             moduleTypeNameByID(name,moduleid);
             serverLog(LL_WARNING,"The RDB file contains module data I can't load: no matching module '%s'", name);
             exit(1);
         }
         RedisModuleIO io;
         moduleInitIOContext(io,mt,rdb);
+        io.ver = (rdbtype == RDB_TYPE_MODULE) ? 1 : 2;
         /* Call the rdb_load method of the module providing the 10 bit
          * encoding version in the lower 10 bits of the module ID. */
         void *ptr = mt->rdb_load(&io,moduleid&1023);
+
+        /* Module v2 serialization has an EOF mark at the end. */
+        if (io.ver == 2) {
+            uint64_t eof = rdbLoadLen(rdb,NULL);
+            if (eof != RDB_MODULE_OPCODE_EOF) {
+                serverLog(LL_WARNING,"The RDB file contains module data for the module '%s' that is not terminated by the proper module value EOF marker", name);
+                exit(1);
+            }
+        }
+
         if (ptr == NULL) {
             moduleTypeNameByID(name,moduleid);
             serverLog(LL_WARNING,"The RDB file contains module data for the module type '%s', that the responsible module is not able to load. Check for modules log above for additional clues.", name);