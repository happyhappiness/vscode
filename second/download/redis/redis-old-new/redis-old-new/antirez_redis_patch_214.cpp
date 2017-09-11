@@ -275,7 +275,8 @@ static char* loadStringObject() {
             return loadLzfStringObject();
         default:
             /* unknown encoding */
-            SHIFT_ERROR(offset, "Unknown string encoding (0x%02llx)", len);
+            SHIFT_ERROR(offset, "Unknown string encoding (0x%02llx)",
+                (unsigned long long) len);
             return NULL;
         }
     }
@@ -390,7 +391,8 @@ static int loadPair(entry *e) {
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element at index %llu (length: %llu)", i, length);
+                SHIFT_ERROR(offset, "Error reading element at index %llu (length: %llu)",
+                    (unsigned long long) i, (unsigned long long) length);
                 return 0;
             }
         }
@@ -399,12 +401,14 @@ static int loadPair(entry *e) {
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element key at index %llu (length: %llu)", i, length);
+                SHIFT_ERROR(offset, "Error reading element key at index %llu (length: %llu)",
+                    (unsigned long long) i, (unsigned long long) length);
                 return 0;
             }
             offset = CURR_OFFSET;
             if (!processDoubleValue(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element value at index %llu (length: %llu)", i, length);
+                SHIFT_ERROR(offset, "Error reading element value at index %llu (length: %llu)",
+                    (unsigned long long) i, (unsigned long long) length);
                 return 0;
             }
         }
@@ -413,12 +417,14 @@ static int loadPair(entry *e) {
         for (i = 0; i < length; i++) {
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element key at index %llu (length: %llu)", i, length);
+                SHIFT_ERROR(offset, "Error reading element key at index %llu (length: %llu)",
+                    (unsigned long long) i, (unsigned long long) length);
                 return 0;
             }
             offset = CURR_OFFSET;
             if (!processStringObject(NULL)) {
-                SHIFT_ERROR(offset, "Error reading element value at index %llu (length: %llu)", i, length);
+                SHIFT_ERROR(offset, "Error reading element value at index %llu (length: %llu)",
+                    (unsigned long long) i, (unsigned long long) length);
                 return 0;
             }
         }
@@ -451,7 +457,8 @@ static entry loadEntry() {
             return e;
         }
         if (length > 63) {
-            SHIFT_ERROR(offset[1], "Database number out of range (%llu)", length);
+            SHIFT_ERROR(offset[1], "Database number out of range (%llu)",
+                (unsigned long long) length);
             return e;
         }
     } else if (e.type == RDB_OPCODE_EOF) {