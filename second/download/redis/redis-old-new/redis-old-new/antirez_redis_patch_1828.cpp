@@ -39,11 +39,13 @@
 #include <errno.h>
 #include <sys/stat.h>
 #include <sys/time.h>
+#include <assert.h>
 
 #include "hiredis.h"
 #include "sds.h"
 #include "zmalloc.h"
 #include "linenoise.h"
+#include "help.h"
 
 #define REDIS_NOTUSED(V) ((void) V)
 
@@ -84,6 +86,149 @@ static long long mstime(void) {
 }
 
 /*------------------------------------------------------------------------------
+ * Help functions
+ *--------------------------------------------------------------------------- */
+
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
+/* Output command help to stdout. */
+static void cliOutputCommandHelp(struct commandHelp *help, int group) {
+    printf("\r\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\r\n", help->name, help->params);
+    printf("  \x1b[33msummary:\x1b[0m %s\r\n", help->summary);
+    printf("  \x1b[33msince:\x1b[0m %s\r\n", help->since);
+    if (group) {
+        printf("  \x1b[33mgroup:\x1b[0m %s\r\n", commandGroups[help->group]);
+    }
+}
+
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
+}
+
+/* Output all command help, filtering by group or command name. */
+static void cliOutputHelp(int argc, char **argv) {
+    int i, j, len;
+    int group = -1;
+    helpEntry *entry;
+    struct commandHelp *help;
+
+    if (argc == 0) {
+        cliOutputGenericHelp();
+        return;
+    } else if (argc > 0 && argv[0][0] == '@') {
+        len = sizeof(commandGroups)/sizeof(char*);
+        for (i = 0; i < len; i++) {
+            if (strcasecmp(argv[0]+1,commandGroups[i]) == 0) {
+                group = i;
+                break;
+            }
+        }
+    }
+
+    assert(argc > 0);
+    for (i = 0; i < helpEntriesLen; i++) {
+        entry = &helpEntries[i];
+        if (entry->type != CLI_HELP_COMMAND) continue;
+
+        help = entry->org;
+        if (group == -1) {
+            /* Compare all arguments */
+            if (argc == entry->argc) {
+                for (j = 0; j < argc; j++) {
+                    if (strcasecmp(argv[j],entry->argv[j]) != 0) break;
+                }
+                if (j == argc) {
+                    cliOutputCommandHelp(help,1);
+                }
+            }
+        } else {
+            if (group == help->group) {
+                cliOutputCommandHelp(help,0);
+            }
+        }
+    }
+    printf("\r\n");
+}
+
+static void completionCallback(const char *buf, linenoiseCompletions *lc) {
+    size_t startpos = 0;
+    int mask;
+    int i;
+    size_t matchlen;
+    sds tmp;
+
+    if (strncasecmp(buf,"help ",5) == 0) {
+        startpos = 5;
+        while (isspace(buf[startpos])) startpos++;
+        mask = CLI_HELP_COMMAND | CLI_HELP_GROUP;
+    } else {
+        mask = CLI_HELP_COMMAND;
+    }
+
+    for (i = 0; i < helpEntriesLen; i++) {
+        if (!(helpEntries[i].type & mask)) continue;
+
+        matchlen = strlen(buf+startpos);
+        if (strncasecmp(buf+startpos,helpEntries[i].full,matchlen) == 0) {
+            tmp = sdsnewlen(buf,startpos);
+            tmp = sdscat(tmp,helpEntries[i].full);
+            linenoiseAddCompletion(lc,tmp);
+            sdsfree(tmp);
+        }
+    }
+}
+
+/*------------------------------------------------------------------------------
  * Networking / parsing
  *--------------------------------------------------------------------------- */
 
@@ -252,22 +397,6 @@ static int cliReadReply() {
     return REDIS_OK;
 }
 
-static void showInteractiveHelp(void) {
-    printf(
-    "\n"
-    "Welcome to redis-cli " REDIS_VERSION "!\n"
-    "Just type any valid Redis command to see a pretty printed output.\n"
-    "\n"
-    "It is possible to quote strings, like in:\n"
-    "  set \"my key\" \"some string \\xff\\n\"\n"
-    "\n"
-    "You can find a list of valid Redis commands at\n"
-    "  http://code.google.com/p/redis/wiki/CommandReference\n"
-    "\n"
-    "Note: redis-cli supports line editing, use up/down arrows for history."
-    "\n\n");
-}
-
 static int cliSendCommand(int argc, char **argv, int repeat) {
     char *command = argv[0];
     size_t *argvlen;
@@ -279,8 +408,8 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     }
 
     config.raw_output = !strcasecmp(command,"info");
-    if (!strcasecmp(command,"help")) {
-        showInteractiveHelp();
+    if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
+        cliOutputHelp(--argc, ++argv);
         return REDIS_OK;
     }
     if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
@@ -412,6 +541,8 @@ static void repl() {
     sds *argv;
 
     config.interactive = 1;
+    linenoiseSetCompletionCallback(completionCallback);
+
     while((line = linenoise(context ? "redis> " : "not connected> ")) != NULL) {
         if (line[0] != '\0') {
             argv = sdssplitargs(line,&argc);
@@ -430,6 +561,8 @@ static void repl() {
                     config.hostip = sdsnew(argv[1]);
                     config.hostport = atoi(argv[2]);
                     cliConnect(1);
+                } else if (argc == 1 && !strcasecmp(argv[0],"clear")) {
+                    linenoiseClearScreen();
                 } else {
                     long long start_time = mstime(), elapsed;
 
@@ -489,6 +622,7 @@ int main(int argc, char **argv) {
     config.historyfile = NULL;
     config.tty = isatty(fileno(stdout)) || (getenv("FAKETTY") != NULL);
     config.mb_sep = '\n';
+    cliInitHelp();
 
     if (getenv("HOME") != NULL) {
         config.historyfile = malloc(256);