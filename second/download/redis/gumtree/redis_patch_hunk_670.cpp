         tmp.type = CLI_HELP_COMMAND;
         tmp.org = &commandHelp[i];
         helpEntries[pos++] = tmp;
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
+}
+
 /* Output command help to stdout. */
 static void cliOutputCommandHelp(struct commandHelp *help, int group) {
     printf("\r\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\r\n", help->name, help->params);
     printf("  \x1b[33msummary:\x1b[0m %s\r\n", help->summary);
     printf("  \x1b[33msince:\x1b[0m %s\r\n", help->since);
     if (group) {
