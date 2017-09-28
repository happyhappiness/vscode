                     hashTypeConvert(o, OBJ_ENCODING_HT);
                 break;
             default:
                 rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
                 break;
         }
+    } else if (rdbtype == RDB_TYPE_MODULE || rdbtype == RDB_TYPE_MODULE_2) {
+        uint64_t moduleid = rdbLoadLen(rdb,NULL);
+        moduleType *mt = moduleTypeLookupModuleByID(moduleid);
+        char name[10];
+
+        if (rdbCheckMode && rdbtype == RDB_TYPE_MODULE_2)
+            return rdbLoadCheckModuleValue(rdb,name);
+
+        if (mt == NULL) {
+            moduleTypeNameByID(name,moduleid);
+            serverLog(LL_WARNING,"The RDB file contains module data I can't load: no matching module '%s'", name);
+            exit(1);
+        }
+        RedisModuleIO io;
+        moduleInitIOContext(io,mt,rdb);
+        io.ver = (rdbtype == RDB_TYPE_MODULE) ? 1 : 2;
+        /* Call the rdb_load method of the module providing the 10 bit
+         * encoding version in the lower 10 bits of the module ID. */
+        void *ptr = mt->rdb_load(&io,moduleid&1023);
+        if (io.ctx) {
+            moduleFreeContext(io.ctx);
+            zfree(io.ctx);
+        }
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
+        if (ptr == NULL) {
+            moduleTypeNameByID(name,moduleid);
+            serverLog(LL_WARNING,"The RDB file contains module data for the module type '%s', that the responsible module is not able to load. Check for modules log above for additional clues.", name);
+            exit(1);
+        }
+        o = createModuleObject(mt,ptr);
     } else {
         rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
     }
     return o;
 }
 
