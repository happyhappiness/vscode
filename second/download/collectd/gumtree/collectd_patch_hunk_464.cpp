 }
 
 static char *
 uuid_parse_dmidecode(FILE *file)
 {
     char line[1024];
-    int inSysInfo = 0;
 
-    for (;;) {
-        if (!fgets(line, sizeof(line)/sizeof(char), file)) {
-            return NULL;
-        }
-        if (strncmp(line, HANDLE_PREFIX,
-                    (sizeof(HANDLE_PREFIX)/sizeof(char))-1) == 0) {
-            /*printf("Got handle %s\n", line);*/
-            inSysInfo = 0;
-        } else if (strncmp(line, SYSINFO_PREFIX,
-                           (sizeof(SYSINFO_PREFIX)/sizeof(char))-1) == 0) {
-            /*printf("Got system info %s\n", line);*/
-            inSysInfo = 1;
-        } else if (strncmp(line, ALT_SYSINFO_PREFIX,
-                           (sizeof(ALT_SYSINFO_PREFIX)/sizeof(char))-1) == 0) {
-            /*printf("Got alt system info %s\n", line);*/
-            inSysInfo = 1;
-        }
-        
-        if (inSysInfo) {
-            if (strncmp(line, UUID_PREFIX,
-                        (sizeof(UUID_PREFIX)/sizeof(char))-1) == 0) {
-                char *uuid = line + (sizeof(UUID_PREFIX)/sizeof(char));
-                /*printf("Got uuid [%s]\n", uuid);*/
-                if (looks_like_a_uuid (uuid))
-                    return strdup (uuid);
-            }
-            if (strncmp(line, ALT_UUID_PREFIX,
-                        (sizeof(ALT_UUID_PREFIX)/sizeof(char))-1) == 0) {
-                char *uuid = line + (sizeof(ALT_UUID_PREFIX)/sizeof(char));
-                /*printf("Got alt uuid [%s]\n", uuid);*/
-                if (looks_like_a_uuid (uuid))
-                    return strdup (uuid);
-            }
-        }
+    while (fgets (line, sizeof (line), file) != NULL)
+    {
+        char *fields[4];
+        int fields_num;
+
+        strstripnewline (line);
+
+        /* Look for a line reading:
+         *   UUID: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
+         */
+        fields_num = strsplit (line, fields, STATIC_ARRAY_SIZE (fields));
+        if (fields_num != 2)
+            continue;
+
+        if (strcmp("UUID:", fields[0]) != 0)
+            continue;
+
+        if (!looks_like_a_uuid (fields[1]))
+            continue;
+
+        return strdup (fields[1]);
     }
     return NULL;
 }
 
 static char *
 uuid_get_from_dmidecode(void)
