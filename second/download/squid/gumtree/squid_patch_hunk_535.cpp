 {
     char *token = strtok(NULL, w_space);
 
     if (token == NULL)
         self_destruct();
 
-    if (!strcasecmp(token, "on")) {
+    if (!strcmp(token, "on")) {
         *var = 1;
-    } else if (!strcasecmp(token, "enable")) {
+    } else if (!strcmp(token, "enable")) {
         debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'enable' is deprecated. Please update to use value 'on'.");
         *var = 1;
-    } else if (!strcasecmp(token, "warn")) {
+    } else if (!strcmp(token, "warn")) {
         *var = -1;
-    } else if (!strcasecmp(token, "off")) {
+    } else if (!strcmp(token, "off")) {
         *var = 0;
-    } else if (!strcasecmp(token, "disable")) {
+    } else if (!strcmp(token, "disable")) {
         debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'disable' is deprecated. Please update to use value 'off'.");
         *var = 0;
     } else {
         debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Invalid option: Tristate options can only be 'on', 'off', or 'warn'.");
         self_destruct();
     }
 }
 
 #define free_tristate free_int
 
+void
+parse_pipelinePrefetch(int *var)
+{
+    char *token = ConfigParser::strtokFile();
+
+    if (token == NULL)
+        self_destruct();
+
+    if (!strcmp(token, "on")) {
+        debugs(0, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: 'pipeline_prefetch on' is deprecated. Please update to use 1 (or a higher number).");
+        *var = 1;
+    } else if (!strcmp(token, "off")) {
+        debugs(0, DBG_PARSE_NOTE(2), "WARNING: 'pipeline_prefetch off' is deprecated. Please update to use '0'.");
+        *var = 0;
+    } else {
+        ConfigParser::strtokFileUndo();
+        parse_int(var);
+    }
+}
+
+#define free_pipelinePrefetch free_int
+#define dump_pipelinePrefetch dump_int
+
 static void
 dump_refreshpattern(StoreEntry * entry, const char *name, RefreshPattern * head)
 {
     while (head != NULL) {
         storeAppendPrintf(entry, "%s%s %s %d %d%% %d",
                           name,
