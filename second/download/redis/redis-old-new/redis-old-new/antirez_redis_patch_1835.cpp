@@ -89,6 +89,50 @@ static long long mstime(void) {
  * Help functions
  *--------------------------------------------------------------------------- */
 
+#define CLI_HELP_COMMAND 1
+#define CLI_HELP_GROUP 2
+
+typedef struct {
+    int type;
+    int argc;
+    sds *argv;
+    sds full;
+
+    /* Only used for help on commands */
+    struct commandHelp *org;
+} helpEntry;
+
+static helpEntry *helpEntries;
+static int helpEntriesLen;
+
+static void cliInitHelp() {
+    int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
+    int groupslen = sizeof(commandGroups)/sizeof(char*);
+    int i, len, pos = 0;
+    helpEntry tmp;
+
+    helpEntriesLen = len = commandslen+groupslen;
+    helpEntries = malloc(sizeof(helpEntry)*len);
+
+    for (i = 0; i < groupslen; i++) {
+        tmp.argc = 1;
+        tmp.argv = malloc(sizeof(sds));
+        tmp.argv[0] = sdscatprintf(sdsempty(),"@%s",commandGroups[i]);
+        tmp.full = tmp.argv[0];
+        tmp.type = CLI_HELP_GROUP;
+        tmp.org = NULL;
+        helpEntries[pos++] = tmp;
+    }
+
+    for (i = 0; i < commandslen; i++) {
+        tmp.argv = sdssplitargs(commandHelp[i].name,&tmp.argc);
+        tmp.full = sdsnew(commandHelp[i].name);
+        tmp.type = CLI_HELP_COMMAND;
+        tmp.org = &commandHelp[i];
+        helpEntries[pos++] = tmp;
+    }
+}
+
 /* Output command help to stdout. */
 static void cliOutputCommandHelp(struct commandHelp *help, int group) {
     printf("\r\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\r\n", help->name, help->params);
@@ -113,9 +157,10 @@ static void cliOutputGenericHelp() {
 
 /* Output all command help, filtering by group or command name. */
 static void cliOutputHelp(int argc, char **argv) {
-    int i, len;
-    struct commandHelp *help;
+    int i, j, len;
     int group = -1;
+    helpEntry *entry;
+    struct commandHelp *help;
 
     if (argc == 0) {
         cliOutputGenericHelp();
@@ -130,13 +175,21 @@ static void cliOutputHelp(int argc, char **argv) {
         }
     }
 
-    len = sizeof(commandHelp)/sizeof(struct commandHelp);
     assert(argc > 0);
-    for (i = 0; i < len; i++) {
-        help = &commandHelp[i];
+    for (i = 0; i < helpEntriesLen; i++) {
+        entry = &helpEntries[i];
+        if (entry->type != CLI_HELP_COMMAND) continue;
+
+        help = entry->org;
         if (group == -1) {
-            if (strcasecmp(help->name, argv[0]) == 0) {
-                cliOutputCommandHelp(help,1);
+            /* Compare all arguments */
+            if (argc == entry->argc) {
+                for (j = 0; j < argc; j++) {
+                    if (strcasecmp(argv[j],entry->argv[j]) != 0) break;
+                }
+                if (j == argc) {
+                    cliOutputCommandHelp(help,1);
+                }
             }
         } else {
             if (group == help->group) {
@@ -147,69 +200,30 @@ static void cliOutputHelp(int argc, char **argv) {
     printf("\r\n");
 }
 
-#define CLI_COMPLETE_COMMAND 1
-#define CLI_COMPLETE_GROUP 2
-
-typedef struct {
-    char *name;
-    int type;
-} completionEntry;
-
-static completionEntry *completionEntries;
-static int completionEntriesLen;
-
-/* Build 2 different arrays for completion. One for raw command completion and one
- * for completion using HELP (including groups). */
-static void cliInitHelp() {
-    int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
-    int groupslen = sizeof(commandGroups)/sizeof(char*);
-    int i, len, pos = 0;
-    completionEntry tmp;
-
-    completionEntriesLen = len = commandslen+groupslen;
-    completionEntries = malloc(sizeof(completionEntry)*len);
-
-    for (i = 0; i < groupslen; i++) {
-        tmp.name = malloc(strlen(commandGroups[i]+2));
-        sprintf(tmp.name,"@%s",commandGroups[i]);
-        tmp.type = CLI_COMPLETE_GROUP;
-        completionEntries[pos++] = tmp;
-    }
-
-    for (i = 0; i < commandslen; i++) {
-        tmp.name = commandHelp[i].name;
-        tmp.type = CLI_COMPLETE_COMMAND;
-        completionEntries[pos++] = tmp;
-    }
-}
-
 static void completionCallback(const char *buf, linenoiseCompletions *lc) {
     size_t startpos = 0;
     int mask;
     int i;
     size_t matchlen;
-    char *tmp;
-    size_t tmpsize;
+    sds tmp;
 
     if (strncasecmp(buf,"help ",5) == 0) {
         startpos = 5;
         while (isspace(buf[startpos])) startpos++;
-        mask = CLI_COMPLETE_COMMAND | CLI_COMPLETE_GROUP;
+        mask = CLI_HELP_COMMAND | CLI_HELP_GROUP;
     } else {
-        mask = CLI_COMPLETE_COMMAND;
+        mask = CLI_HELP_COMMAND;
     }
 
-    for (i = 0; i < completionEntriesLen; i++) {
-        if (!(completionEntries[i].type & mask)) continue;
+    for (i = 0; i < helpEntriesLen; i++) {
+        if (!(helpEntries[i].type & mask)) continue;
 
         matchlen = strlen(buf+startpos);
-        if (strncasecmp(buf+startpos,completionEntries[i].name,matchlen) == 0) {
-            tmpsize = startpos+strlen(completionEntries[i].name)+1;
-            tmp = malloc(tmpsize);
-            memcpy(tmp,buf,startpos);
-            memcpy(tmp+startpos,completionEntries[i].name,tmpsize-startpos);
+        if (strncasecmp(buf+startpos,helpEntries[i].full,matchlen) == 0) {
+            tmp = sdsnewlen(buf,startpos);
+            tmp = sdscat(tmp,helpEntries[i].full);
             linenoiseAddCompletion(lc,tmp);
-            free(tmp);
+            sdsfree(tmp);
         }
     }
 }