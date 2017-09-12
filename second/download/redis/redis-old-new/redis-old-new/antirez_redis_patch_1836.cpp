@@ -39,6 +39,7 @@
 #include <errno.h>
 #include <sys/stat.h>
 #include <sys/time.h>
+#include <assert.h>
 
 #include "hiredis.h"
 #include "sds.h"
@@ -89,58 +90,128 @@ static long long mstime(void) {
  *--------------------------------------------------------------------------- */
 
 /* Output command help to stdout. */
-static void outputCommandHelp(struct commandHelp *help) {
-    printf("\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\n", help->name, help->params);
-    printf("  \x1b[33msummary:\x1b[0m %s\n", help->summary);
-    printf("  \x1b[33msince:\x1b[0m %s\n", help->since);
-    printf("  \x1b[33mgroup:\x1b[0m %s\n", commandGroups[help->group]);
-}
-
-/* Return command group type by name string. */
-static int commandGroupIndex(const char *name) {
-    int i, len = sizeof(commandGroups)/sizeof(char*);
-    for (i = 0; i < len; i++)
-        if (strcasecmp(name, commandGroups[i]) == 0)
-            return i;
-    return -1;
+static void cliOutputCommandHelp(struct commandHelp *help, int group) {
+    printf("\r\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\r\n", help->name, help->params);
+    printf("  \x1b[33msummary:\x1b[0m %s\r\n", help->summary);
+    printf("  \x1b[33msince:\x1b[0m %s\r\n", help->since);
+    if (group) {
+        printf("  \x1b[33mgroup:\x1b[0m %s\r\n", commandGroups[help->group]);
+    }
 }
 
-/* Output group names. */
-static void outputGroupHelp() {
-    int i, len = sizeof(commandGroups)/sizeof(char*);
-    for (i = 0; i < len; i++)
-        printf("  \x1b[90m-\x1b[0m %s\n", commandGroups[i]);
+/* Print generic help. */
+static void cliOutputGenericHelp() {
+    printf(
+        "redis-cli %s\r\n"
+        "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
+        "      \"help <command>\" for help on <command>\r\n"
+        "      \"help <tab>\" to get a list of possible help topics\r\n"
+        "      \"quit\" to exit\r\n",
+        REDIS_VERSION
+    );
 }
 
 /* Output all command help, filtering by group or command name. */
-static void outputHelp(int argc, char **argv) {
-    int i, len = sizeof(commandHelp) / sizeof(struct commandHelp);
-    int group;
+static void cliOutputHelp(int argc, char **argv) {
+    int i, len;
     struct commandHelp *help;
+    int group = -1;
 
-    if (argc && strcasecmp("groups", argv[0]) == 0) {
-        outputGroupHelp();
+    if (argc == 0) {
+        cliOutputGenericHelp();
         return;
+    } else if (argc > 0 && argv[0][0] == '@') {
+        len = sizeof(commandGroups)/sizeof(char*);
+        for (i = 0; i < len; i++) {
+            if (strcasecmp(argv[0]+1,commandGroups[i]) == 0) {
+                group = i;
+                break;
+            }
+        }
     }
 
-    group = argc ? commandGroupIndex(argv[0]) : -1;
+    len = sizeof(commandHelp)/sizeof(struct commandHelp);
+    assert(argc > 0);
     for (i = 0; i < len; i++) {
         help = &commandHelp[i];
         if (group == -1) {
-            if (argc) {
-                if (strcasecmp(help->name, argv[0]) == 0) {
-                    outputCommandHelp(help);
-                }
-            } else {
-                outputCommandHelp(help);
+            if (strcasecmp(help->name, argv[0]) == 0) {
+                cliOutputCommandHelp(help,1);
             }
         } else {
             if (group == help->group) {
-                outputCommandHelp(help);
+                cliOutputCommandHelp(help,0);
             }
         }
     }
-    puts("");
+    printf("\r\n");
+}
+
+#define CLI_COMPLETE_COMMAND 1
+#define CLI_COMPLETE_GROUP 2
+
+typedef struct {
+    char *name;
+    int type;
+} completionEntry;
+
+static completionEntry *completionEntries;
+static int completionEntriesLen;
+
+/* Build 2 different arrays for completion. One for raw command completion and one
+ * for completion using HELP (including groups). */
+static void cliInitHelp() {
+    int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
+    int groupslen = sizeof(commandGroups)/sizeof(char*);
+    int i, len, pos = 0;
+    completionEntry tmp;
+
+    completionEntriesLen = len = commandslen+groupslen;
+    completionEntries = malloc(sizeof(completionEntry)*len);
+
+    for (i = 0; i < groupslen; i++) {
+        tmp.name = malloc(strlen(commandGroups[i]+2));
+        sprintf(tmp.name,"@%s",commandGroups[i]);
+        tmp.type = CLI_COMPLETE_GROUP;
+        completionEntries[pos++] = tmp;
+    }
+
+    for (i = 0; i < commandslen; i++) {
+        tmp.name = commandHelp[i].name;
+        tmp.type = CLI_COMPLETE_COMMAND;
+        completionEntries[pos++] = tmp;
+    }
+}
+
+static void completionCallback(const char *buf, linenoiseCompletions *lc) {
+    size_t startpos = 0;
+    int mask;
+    int i;
+    size_t matchlen;
+    char *tmp;
+    size_t tmpsize;
+
+    if (strncasecmp(buf,"help ",5) == 0) {
+        startpos = 5;
+        while (isspace(buf[startpos])) startpos++;
+        mask = CLI_COMPLETE_COMMAND | CLI_COMPLETE_GROUP;
+    } else {
+        mask = CLI_COMPLETE_COMMAND;
+    }
+
+    for (i = 0; i < completionEntriesLen; i++) {
+        if (!(completionEntries[i].type & mask)) continue;
+
+        matchlen = strlen(buf+startpos);
+        if (strncasecmp(buf+startpos,completionEntries[i].name,matchlen) == 0) {
+            tmpsize = startpos+strlen(completionEntries[i].name)+1;
+            tmp = malloc(tmpsize);
+            memcpy(tmp,buf,startpos);
+            memcpy(tmp+startpos,completionEntries[i].name,tmpsize-startpos);
+            linenoiseAddCompletion(lc,tmp);
+            free(tmp);
+        }
+    }
 }
 
 /*------------------------------------------------------------------------------
@@ -318,8 +389,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     int j;
 
     config.raw_output = !strcasecmp(command,"info");
-    if (!strcasecmp(command,"help")) {
-        outputHelp(--argc, ++argv);
+    if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
+        cliOutputHelp(--argc, ++argv);
         return REDIS_OK;
     }
     if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
@@ -450,6 +521,7 @@ static void repl() {
     sds *argv;
 
     config.interactive = 1;
+    linenoiseSetCompletionCallback(completionCallback);
     while((line = linenoise("redis> ")) != NULL) {
         if (line[0] != '\0') {
             argv = sdssplitargs(line,&argc);
@@ -525,6 +597,7 @@ int main(int argc, char **argv) {
     config.historyfile = NULL;
     config.tty = isatty(fileno(stdout)) || (getenv("FAKETTY") != NULL);
     config.mb_sep = '\n';
+    cliInitHelp();
 
     if (getenv("HOME") != NULL) {
         config.historyfile = malloc(256);