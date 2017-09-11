@@ -223,7 +223,8 @@ int redis_check_rdb(char *rdbfilename) {
             if ((auxkey = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
             if ((auxval = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
 
-            rdbCheckInfo("%s = '%s'", (char*)auxkey->ptr, (char*)auxval->ptr);
+            rdbCheckInfo("AUX FIELD %s = '%s'",
+                (char*)auxkey->ptr, (char*)auxval->ptr);
             decrRefCount(auxkey);
             decrRefCount(auxval);
             continue; /* Read type again. */
@@ -265,6 +266,8 @@ int redis_check_rdb(char *rdbfilename) {
             rdbCheckInfo("RDB file was saved with checksum disabled: no check performed.");
         } else if (cksum != expected) {
             rdbCheckError("RDB CRC error");
+        } else {
+            rdbCheckInfo("Checksum OK");
         }
     }
 