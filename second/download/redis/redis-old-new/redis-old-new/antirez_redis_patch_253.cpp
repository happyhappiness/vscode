@@ -130,6 +130,7 @@ static void usage(void);
 static void slaveMode(void);
 char *redisGitSHA1(void);
 char *redisGitDirty(void);
+static int cliConnect(int force);
 
 /*------------------------------------------------------------------------------
  * Utility functions
@@ -238,11 +239,11 @@ static void cliInitHelp(void) {
     helpEntry tmp;
 
     helpEntriesLen = len = commandslen+groupslen;
-    helpEntries = malloc(sizeof(helpEntry)*len);
+    helpEntries = zmalloc(sizeof(helpEntry)*len);
 
     for (i = 0; i < groupslen; i++) {
         tmp.argc = 1;
-        tmp.argv = malloc(sizeof(sds));
+        tmp.argv = zmalloc(sizeof(sds));
         tmp.argv[0] = sdscatprintf(sdsempty(),"@%s",commandGroups[i]);
         tmp.full = tmp.argv[0];
         tmp.type = CLI_HELP_GROUP;
@@ -259,6 +260,64 @@ static void cliInitHelp(void) {
     }
 }
 
+/* cliInitHelp() setups the helpEntries array with the command and group
+ * names from the help.h file. However the Redis instance we are connecting
+ * to may support more commands, so this function integrates the previous
+ * entries with additional entries obtained using the COMMAND command
+ * available in recent versions of Redis. */
+static void cliIntegrateHelp(void) {
+    if (cliConnect(0) == REDIS_ERR) return;
+
+    redisReply *reply = redisCommand(context, "COMMAND");
+    if(reply == NULL || reply->type != REDIS_REPLY_ARRAY) return;
+
+    /* Scan the array reported by COMMAND and fill only the entries that
+     * don't already match what we have. */
+    for (size_t j = 0; j < reply->elements; j++) {
+        redisReply *entry = reply->element[j];
+        char *cmdname = entry->element[0]->str;
+        int i;
+
+        for (i = 0; i < helpEntriesLen; i++) {
+            helpEntry *he = helpEntries+i;
+            if (!strcasecmp(he->argv[0],cmdname))
+                break;
+        }
+        if (i != helpEntriesLen) continue;
+        printf("%s\n", cmdname);
+
+        helpEntriesLen++;
+        helpEntries = zrealloc(helpEntries,sizeof(helpEntry)*helpEntriesLen);
+        helpEntry *new = helpEntries+(helpEntriesLen-1);
+
+        new->argc = 1;
+        new->argv = zmalloc(sizeof(sds));
+        new->argv[0] = sdsnew(cmdname);
+        new->full = new->argv[0];
+        new->type = CLI_HELP_COMMAND;
+        sdstoupper(new->argv[0]);
+
+        struct commandHelp *ch = zmalloc(sizeof(*ch));
+        ch->name = new->argv[0];
+        ch->params = sdsempty();
+        int args = llabs(entry->element[1]->integer);
+        if (entry->element[3]->integer == 1) {
+            ch->params = sdscat(ch->params,"key ");
+            args--;
+        }
+        while(args--) ch->params = sdscat(ch->params,"arg ");
+        if (entry->element[1]->integer < 0)
+            ch->params = sdscat(ch->params,"...options...");
+        ch->summary = "Help not available";
+        ch->group = 0;
+        ch->since = "not known";
+        new->org = ch;
+    }
+    freeReplyObject(reply);
+
+    printf("%s\n", helpEntries[80].full);
+}
+
 /* Output command help to stdout. */
 static void cliOutputCommandHelp(struct commandHelp *help, int group) {
     printf("\r\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\r\n", help->name, help->params);
@@ -828,7 +887,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     }
 
     /* Setup argument length */
-    argvlen = malloc(argc*sizeof(size_t));
+    argvlen = zmalloc(argc*sizeof(size_t));
     for (j = 0; j < argc; j++)
         argvlen[j] = sdslen(argv[j]);
 
@@ -851,12 +910,12 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
             printf("Entering slave output mode...  (press Ctrl-C to quit)\n");
             slaveMode();
             config.slave_mode = 0;
-            free(argvlen);
+            zfree(argvlen);
             return REDIS_ERR;  /* Error = slaveMode lost connection to master */
         }
 
         if (cliReadReply(output_raw) != REDIS_OK) {
-            free(argvlen);
+            zfree(argvlen);
             return REDIS_ERR;
         } else {
             /* Store database number when SELECT was successfully executed. */
@@ -871,7 +930,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         fflush(stdout); /* Make it grep friendly */
     }
 
-    free(argvlen);
+    zfree(argvlen);
     return REDIS_OK;
 }
 
@@ -1235,7 +1294,7 @@ static void repl(void) {
 
             if (argv == NULL) {
                 printf("Invalid argument(s)\n");
-                free(line);
+                linenoiseFree(line);
                 continue;
             } else if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||
@@ -1294,7 +1353,7 @@ static void repl(void) {
             sdsfreesplitres(argv,argc);
         }
         /* linenoise() returns malloc-ed lines like readline() */
-        free(line);
+        linenoiseFree(line);
     }
     exit(0);
 }
@@ -2159,7 +2218,7 @@ static char *getInfoField(char *info, char *field) {
     n1 = strchr(p,'\r');
     n2 = strchr(p,',');
     if (n2 && n2 < n1) n1 = n2;
-    result = malloc(sizeof(char)*(n1-p)+1);
+    result = zmalloc(sizeof(char)*(n1-p)+1);
     memcpy(result,p,(n1-p));
     result[n1-p] = '\0';
     return result;
@@ -2173,7 +2232,7 @@ static long getLongInfoField(char *info, char *field) {
 
     if (!value) return LONG_MIN;
     l = strtol(value,NULL,10);
-    free(value);
+    zfree(value);
     return l;
 }
 
@@ -2536,6 +2595,7 @@ int main(int argc, char **argv) {
         config.output = OUTPUT_STANDARD;
     config.mb_delim = sdsnew("\n");
     cliInitHelp();
+    cliIntegrateHelp();
 
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;