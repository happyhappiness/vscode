@@ -28,9 +28,33 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-
 #include "redis.h"
 
+#include <fcntl.h>
+#include <sys/stat.h>
+
+static struct {
+    const char     *name;
+    const int       value;
+} validSyslogFacilities[] = {
+    {"user",    LOG_USER},
+    {"local0",  LOG_LOCAL0},
+    {"local1",  LOG_LOCAL1},
+    {"local2",  LOG_LOCAL2},
+    {"local3",  LOG_LOCAL3},
+    {"local4",  LOG_LOCAL4},
+    {"local5",  LOG_LOCAL5},
+    {"local6",  LOG_LOCAL6},
+    {"local7",  LOG_LOCAL7},
+    {NULL, 0}
+};
+
+clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_LIMIT_NUM_CLASSES] = {
+    {0, 0, 0}, /* normal */
+    {1024*1024*256, 1024*1024*64, 60}, /* slave */
+    {1024*1024*32, 1024*1024*8, 60}  /* pubsub */
+};
+
 /*-----------------------------------------------------------------------------
  * Config file parsing
  *----------------------------------------------------------------------------*/
@@ -140,12 +164,9 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
             FILE *logfp;
 
+            zfree(server.logfile);
             server.logfile = zstrdup(argv[1]);
-            if (!strcasecmp(server.logfile,"stdout")) {
-                zfree(server.logfile);
-                server.logfile = NULL;
-            }
-            if (server.logfile) {
+            if (server.logfile[0] != '\0') {
                 /* Test if we are able to open the file. The server will not
                  * be able to abort just for this problem later... */
                 logfp = fopen(server.logfile,"a");
@@ -164,21 +185,6 @@ void loadServerConfigFromString(char *config) {
             if (server.syslog_ident) zfree(server.syslog_ident);
             server.syslog_ident = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"syslog-facility") && argc == 2) {
-            struct {
-                const char     *name;
-                const int       value;
-            } validSyslogFacilities[] = {
-                {"user",    LOG_USER},
-                {"local0",  LOG_LOCAL0},
-                {"local1",  LOG_LOCAL1},
-                {"local2",  LOG_LOCAL2},
-                {"local3",  LOG_LOCAL3},
-                {"local4",  LOG_LOCAL4},
-                {"local5",  LOG_LOCAL5},
-                {"local6",  LOG_LOCAL6},
-                {"local7",  LOG_LOCAL7},
-                {NULL, 0}
-            };
             int i;
 
             for (i = 0; validSyslogFacilities[i].name; i++) {
@@ -250,7 +256,7 @@ void loadServerConfigFromString(char *config) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"repl-backlog-size") && argc == 2) {
-            long long size = strtoll(argv[1],NULL,10);
+            long long size = memtoll(argv[1],NULL);
             if (size <= 0) {
                 err = "repl-backlog-size must be 1 or greater.";
                 goto loaderr;
@@ -513,7 +519,7 @@ void loadServerConfig(char *filename, char *options) {
 }
 
 /*-----------------------------------------------------------------------------
- * CONFIG command for remote configuration
+ * CONFIG SET implementation
  *----------------------------------------------------------------------------*/
 
 void configSetCommand(redisClient *c) {
@@ -813,6 +819,10 @@ void configSetCommand(redisClient *c) {
             (char*)c->argv[2]->ptr);
 }
 
+/*-----------------------------------------------------------------------------
+ * CONFIG GET implementation
+ *----------------------------------------------------------------------------*/
+
 #define config_get_string_field(_name,_var) do { \
     if (stringmatch(pattern,_name,0)) { \
         addReplyBulkCString(c,_name); \
@@ -1038,6 +1048,620 @@ void configGetCommand(redisClient *c) {
     setDeferredMultiBulkLength(c,replylen,matches*2);
 }
 
+/*-----------------------------------------------------------------------------
+ * CONFIG REWRITE implementation
+ *----------------------------------------------------------------------------*/
+
+/* IGNORE:
+ *
+ * rename-command
+ * include
+ *
+ * Special handling:
+ *
+ * notify-keyspace-events
+ * client-output-buffer-limit
+ * save
+ * appendonly
+ * appendfsync
+ * dir
+ * maxmemory-policy
+ * loglevel
+ * unixsocketperm
+ * slaveof
+ *
+ * Type of config directives:
+ *
+ * CUSTOM
+ * VERBATIM
+ * YESNO
+ * L
+ * LL
+ *
+ */
+
+/* We use the following dictionary type to store where a configuration
+ * option is mentioned in the old configuration file, so it's
+ * like "maxmemory" -> list of line numbers (first line is zero). */
+unsigned int dictSdsHash(const void *key);
+int dictSdsKeyCompare(void *privdata, const void *key1, const void *key2);
+void dictSdsDestructor(void *privdata, void *val);
+void dictListDestructor(void *privdata, void *val);
+
+dictType optionToLineDictType = {
+    dictSdsHash,                /* hash function */
+    NULL,                       /* key dup */
+    NULL,                       /* val dup */
+    dictSdsKeyCompare,          /* key compare */
+    dictSdsDestructor,          /* key destructor */
+    dictListDestructor          /* val destructor */
+};
+
+/* The config rewrite state. */
+struct rewriteConfigState {
+    dict *option_to_line; /* Option -> list of config file lines map */
+    int numlines;         /* Number of lines in current config */
+    sds *lines;           /* Current lines as an array of sds strings */
+    int has_tail;         /* True if we already added directives that were
+                             not present in the original config file. */
+};
+
+/* Append the new line to the current configuration state. */
+void rewriteConfigAppendLine(struct rewriteConfigState *state, sds line) {
+    state->lines = zrealloc(state->lines, sizeof(char*) * (state->numlines+1));
+    state->lines[state->numlines++] = line;
+}
+
+/* Populate the option -> list of line numbers map. */
+void rewriteConfigAddLineNumberToOption(struct rewriteConfigState *state, sds option, int linenum) {
+    list *l = dictFetchValue(state->option_to_line,option);
+
+    if (l == NULL) {
+        l = listCreate();
+        dictAdd(state->option_to_line,sdsdup(option),l);
+    }
+    listAddNodeTail(l,(void*)(long)linenum);
+}
+
+/* Read the old file, split it into lines to populate a newly created
+ * config rewrite state, and return it to the caller.
+ *
+ * If it is impossible to read the old file, NULL is returned.
+ * If the old file does not exist at all, an empty state is returned. */
+struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
+    FILE *fp = fopen(path,"r");
+    struct rewriteConfigState *state = zmalloc(sizeof(*state));
+    char buf[REDIS_CONFIGLINE_MAX+1];
+    int linenum = -1;
+
+    if (fp == NULL && errno != ENOENT) return NULL;
+
+    state->option_to_line = dictCreate(&optionToLineDictType,NULL);
+    state->numlines = 0;
+    state->lines = NULL;
+    state->has_tail = 0;
+    if (fp == NULL) return state;
+
+    /* Read the old file line by line, populate the state. */
+    while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL) {
+        int argc;
+        sds *argv;
+        sds line = sdstrim(sdsnew(buf),"\r\n\t ");
+
+        linenum++; /* Zero based, so we init at -1 */
+
+        /* Handle comments and empty lines. */
+        if (line[0] == '#' || line[0] == '\0') {
+            rewriteConfigAppendLine(state,line);
+            continue;
+        }
+
+        /* Not a comment, split into arguments. */
+        argv = sdssplitargs(line,&argc);
+        if (argv == NULL) {
+            /* Apparently the line is unparsable for some reason, for
+             * instance it may have unbalanced quotes. Load it as a
+             * comment. */
+            sds aux = sdsnew("# ??? ");
+            aux = sdscatsds(aux,line);
+            sdsfree(line);
+            rewriteConfigAppendLine(state,aux);
+            continue;
+        }
+
+        sdstolower(argv[0]); /* We only want lowercase config directives. */
+
+        /* Now we populate the state according to the content of this line.
+         * Append the line and populate the option -> line numbers map. */
+        rewriteConfigAppendLine(state,line);
+        rewriteConfigAddLineNumberToOption(state,argv[0],linenum);
+
+        sdsfreesplitres(argv,argc);
+    }
+    fclose(fp);
+    return state;
+}
+
+/* Rewrite the specified configuration option with the new "line".
+ * It progressively uses lines of the file that were already used for the same
+ * configuraiton option in the old version of the file, removing that line from
+ * the map of options -> line numbers.
+ *
+ * If there are lines associated with a given configuration option and
+ * "force" is non-zero, the line is appended to the configuration file.
+ * Usually "force" is true when an option has not its default value, so it
+ * must be rewritten even if not present previously.
+ * 
+ * The first time a line is appended into a configuration file, a comment
+ * is added to show that starting from that point the config file was generated
+ * by CONFIG REWRITE.
+ *
+ * "line" is either used, or freed, so the caller does not need to free it
+ * in any way. */
+void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sds line, int force) {
+    sds o = sdsnew(option);
+    list *l = dictFetchValue(state->option_to_line,o);
+
+    if (!l && !force) {
+        /* Option not used previously, and we are not forced to use it. */
+        sdsfree(line);
+        sdsfree(o);
+        return;
+    }
+
+    if (l) {
+        listNode *ln = listFirst(l);
+        int linenum = (long) ln->value;
+
+        /* There are still lines in the old configuration file we can reuse
+         * for this option. Replace the line with the new one. */
+        listDelNode(l,ln);
+        if (listLength(l) == 0) dictDelete(state->option_to_line,o);
+        sdsfree(state->lines[linenum]);
+        state->lines[linenum] = line;
+    } else {
+        /* Append a new line. */
+        if (!state->has_tail) {
+            rewriteConfigAppendLine(state,
+                sdsnew("# Generated by CONFIG REWRITE"));
+            state->has_tail = 1;
+        }
+        rewriteConfigAppendLine(state,line);
+    }
+    sdsfree(o);
+}
+
+/* Write the long long 'bytes' value as a string in a way that is parsable
+ * inside redis.conf. If possible uses the GB, MB, KB notation. */
+int rewriteConfigFormatMemory(char *buf, size_t len, long long bytes) {
+    int gb = 1024*1024*1024;
+    int mb = 1024*1024;
+    int kb = 1024;
+
+    if (bytes && (bytes % gb) == 0) {
+        return snprintf(buf,len,"%lldgb",bytes/gb);
+    } else if (bytes && (bytes % mb) == 0) {
+        return snprintf(buf,len,"%lldmb",bytes/mb);
+    } else if (bytes && (bytes % kb) == 0) {
+        return snprintf(buf,len,"%lldkb",bytes/kb);
+    } else {
+        return snprintf(buf,len,"%lld",bytes);
+    }
+}
+
+/* Rewrite a simple "option-name <bytes>" configuration option. */
+void rewriteConfigBytesOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
+    char buf[64];
+    int force = value != defvalue;
+    sds line;
+
+    rewriteConfigFormatMemory(buf,sizeof(buf),value);
+    line = sdscatprintf(sdsempty(),"%s %s",option,buf);
+    rewriteConfigRewriteLine(state,option,line,force);
+
+}
+
+/* Rewrite a yes/no option. */
+void rewriteConfigYesNoOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
+    int force = value != defvalue;
+    sds line = sdscatprintf(sdsempty(),"%s %s",option,
+        value ? "yes" : "no");
+
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite a string option. */
+void rewriteConfigStringOption(struct rewriteConfigState *state, char *option, char *value, char *defvalue) {
+    int force = 1;
+    sds line;
+
+    /* String options set to NULL need to be not present at all in the
+     * configuration file to be set to NULL again at the next reboot. */
+    if (value == NULL) return;
+
+    /* Compare the strings as sds strings to have a binary safe comparison. */
+    if (defvalue && strcmp(value,defvalue) == 0) force = 0;
+
+    line = sdsnew(option);
+    line = sdscatlen(line, " ", 1);
+    line = sdscatrepr(line, value, strlen(value));
+
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite a numerical (long long range) option. */
+void rewriteConfigNumericalOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
+    int force = value != defvalue;
+    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);
+
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite a octal option. */
+void rewriteConfigOctalOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
+    int force = value != defvalue;
+    sds line = sdscatprintf(sdsempty(),"%s %o",option,value);
+
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite an enumeration option, after the "value" every enum/value pair
+ * is specified, terminated by NULL. After NULL the default value is
+ * specified. See how the function is used for more information. */
+void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
+    va_list ap;
+    char *enum_name, *matching_name;
+    int enum_val, def_val, force;
+    sds line;
+    
+    va_start(ap, value);
+    while(1) {
+        enum_name = va_arg(ap,char*);
+        enum_val = va_arg(ap,int);
+        if (enum_name == NULL) {
+            def_val = enum_val;
+            break;
+        }
+        if (value == enum_val) matching_name = enum_name;
+    }
+    va_end(ap);
+    
+    force = value != def_val;
+    line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite the syslog-fability option. */
+void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
+    int value = server.syslog_facility, j;
+    int force = value != LOG_LOCAL0;
+    char *name, *option = "syslog-facility";
+    sds line;
+
+    for (j = 0; validSyslogFacilities[j].name; j++) {
+        if (validSyslogFacilities[j].value == value) {
+            name = (char*) validSyslogFacilities[j].name;
+            break;
+        }
+    }
+    line = sdscatprintf(sdsempty(),"%s %s",option,name);
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite the save option. */
+void rewriteConfigSaveOption(struct rewriteConfigState *state) {
+    int j;
+    sds line;
+
+    /* Note that if there are no save parameters at all, all the current
+     * config line with "save" will be detected as orphaned and deleted,
+     * resulting into no RDB persistence as expected. */
+    for (j = 0; j < server.saveparamslen; j++) {
+        line = sdscatprintf(sdsempty(),"save %ld %d",
+            server.saveparams[j].seconds, server.saveparams[j].changes);
+        rewriteConfigRewriteLine(state,"save",line,1);
+    }
+}
+
+/* Rewrite the dir option, always using absolute paths.*/
+void rewriteConfigDirOption(struct rewriteConfigState *state) {
+    char cwd[1024];
+
+    if (getcwd(cwd,sizeof(cwd)) == NULL) return; /* no rewrite on error. */
+    rewriteConfigStringOption(state,"dir",cwd,NULL);
+}
+
+/* Rewrite the slaveof option. */
+void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
+    char *option = "slaveof";
+    sds line;
+
+    /* If this is a master, we want all the slaveof config options
+     * in the file to be removed. */
+    if (server.masterhost == NULL) return;
+    line = sdscatprintf(sdsempty(),"%s %s %d", option,
+        server.masterhost, server.masterport);
+    rewriteConfigRewriteLine(state,option,line,1);
+}
+
+/* Rewrite the appendonly option. */
+void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
+    int force = server.aof_state != REDIS_AOF_OFF;
+    char *option = "appendonly";
+    sds line;
+    
+    line = sdscatprintf(sdsempty(),"%s %s", option,
+        (server.aof_state == REDIS_AOF_OFF) ? "no" : "yes");
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite the notify-keyspace-events option. */
+void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
+    int force = server.notify_keyspace_events != 0;
+    char *option = "notify-keyspace-events";
+    sds line, flags;
+
+    flags = keyspaceEventsFlagsToString(server.notify_keyspace_events);
+    line = sdsnew(option);
+    line = sdscatlen(line, " ", 1);
+    line = sdscatrepr(line, flags, sdslen(flags));
+    sdsfree(flags);
+    rewriteConfigRewriteLine(state,option,line,force);
+}
+
+/* Rewrite the client-output-buffer-limit option. */
+void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state) {
+    int j;
+    char *option = "client-output-buffer-limit";
+
+    for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
+        int force = (server.client_obuf_limits[j].hard_limit_bytes !=
+                    clientBufferLimitsDefaults[j].hard_limit_bytes) ||
+                    (server.client_obuf_limits[j].soft_limit_bytes !=
+                    clientBufferLimitsDefaults[j].soft_limit_bytes) ||
+                    (server.client_obuf_limits[j].soft_limit_seconds !=
+                    clientBufferLimitsDefaults[j].soft_limit_seconds);
+        sds line;
+        char hard[64], soft[64];
+
+        rewriteConfigFormatMemory(hard,sizeof(hard),
+                server.client_obuf_limits[j].hard_limit_bytes);
+        rewriteConfigFormatMemory(soft,sizeof(soft),
+                server.client_obuf_limits[j].soft_limit_bytes);
+
+        line = sdscatprintf(sdsempty(),"%s %s %s %s %ld",
+                option, getClientLimitClassName(j), hard, soft,
+                (long) server.client_obuf_limits[j].soft_limit_seconds);
+        rewriteConfigRewriteLine(state,option,line,force);
+    }
+}
+
+/* Glue together the configuration lines in the current configuration
+ * rewrite state into a single string, stripping multiple empty lines. */
+sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) {
+    sds content = sdsempty();
+    int j, was_empty = 0;
+
+    for (j = 0; j < state->numlines; j++) {
+        /* Every cluster of empty lines is turned into a single empty line. */
+        if (sdslen(state->lines[j]) == 0) {
+            if (was_empty) continue;
+            was_empty = 1;
+        } else {
+            was_empty = 0;
+        }
+        content = sdscatsds(content,state->lines[j]);
+        content = sdscatlen(content,"\n",1);
+    }
+    return content;
+}
+
+/* Free the configuration rewrite state. */
+void rewriteConfigReleaseState(struct rewriteConfigState *state) {
+    sdsfreesplitres(state->lines,state->numlines);
+    dictRelease(state->option_to_line);
+    zfree(state);
+}
+
+/* At the end of the rewrite process the state contains the remaining
+ * map between "option name" => "lines in the original config file".
+ * Lines used by the rewrite process were removed by the function
+ * rewriteConfigRewriteLine(), all the other lines are "orphaned" and
+ * should be replaced by empty lines.
+ *
+ * This function does just this, iterating all the option names and
+ * blanking all the lines still associated. */
+void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
+    dictIterator *di = dictGetIterator(state->option_to_line);
+    dictEntry *de;
+
+    while((de = dictNext(di)) != NULL) {
+        list *l = dictGetVal(de);
+
+        while(listLength(l)) {
+            listNode *ln = listFirst(l);
+            int linenum = (long) ln->value;
+
+            sdsfree(state->lines[linenum]);
+            state->lines[linenum] = sdsempty();
+            listDelNode(l,ln);
+        }
+    }
+    dictReleaseIterator(di);
+}
+
+/* This function overwrites the old configuration file with the new content.
+ *
+ * 1) The old file length is obtained.
+ * 2) If the new content is smaller, padding is added.
+ * 3) A single write(2) call is used to replace the content of the file.
+ * 4) Later the file is truncated to the length of the new content.
+ *
+ * This way we are sure the file is left in a consistent state even if the
+ * process is stopped between any of the four operations.
+ *
+ * The function returns 0 on success, otherwise -1 is returned and errno
+ * set accordingly. */
+int rewriteConfigOverwriteFile(char *configfile, sds content) {
+    int retval = 0;
+    int fd = open(configfile,O_RDWR|O_CREAT,0644);
+    int content_size = sdslen(content), padding = 0;
+    struct stat sb;
+    sds content_padded;
+
+    /* 1) Open the old file (or create a new one if it does not
+     *    exist), get the size. */
+    if (fd == -1) return -1; /* errno set by open(). */
+    if (fstat(fd,&sb) == -1) {
+        close(fd);
+        return -1; /* errno set by fstat(). */
+    }
+
+    /* 2) Pad the content at least match the old file size. */
+    content_padded = sdsdup(content);
+    if (content_size < sb.st_size) {
+        /* If the old file was bigger, pad the content with
+         * a newline plus as many "#" chars as required. */
+        padding = sb.st_size - content_size;
+        content_padded = sdsgrowzero(content_padded,sb.st_size);
+        content_padded[content_size] = '\n';
+        memset(content_padded+content_size+1,'#',padding-1);
+    }
+
+    /* 3) Write the new content using a single write(2). */
+    if (write(fd,content_padded,strlen(content_padded)) == -1) {
+        retval = -1;
+        goto cleanup;
+    }
+
+    /* 4) Truncate the file to the right length if we used padding. */
+    if (padding) {
+        if (ftruncate(fd,content_size) == -1) {
+            /* Non critical error... */
+        }
+    }
+
+cleanup:
+    sdsfree(content_padded);
+    close(fd);
+    return retval;
+}
+
+/* Rewrite the configuration file at "path".
+ * If the configuration file already exists, we try at best to retain comments
+ * and overall structure.
+ *
+ * Configuration parameters that are at their default value, unless already
+ * explicitly included in the old configuration file, are not rewritten.
+ *
+ * On error -1 is returned and errno is set accordingly, otherwise 0. */
+int rewriteConfig(char *path) {
+    struct rewriteConfigState *state;
+    sds newcontent;
+    int retval;
+
+    /* Step 1: read the old config into our rewrite state. */
+    if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;
+
+    /* Step 2: rewrite every single option, replacing or appending it inside
+     * the rewrite state. */
+
+    /* TODO: Turn every default into a define, use it also in
+     * initServerConfig(). */
+    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
+    rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
+    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
+    rewriteConfigStringOption(state,"bind",server.bindaddr,NULL);
+    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
+    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
+    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
+    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,REDIS_DEFAULT_TCP_KEEPALIVE);
+    rewriteConfigEnumOption(state,"loglevel",server.verbosity,
+        "debug", REDIS_DEBUG,
+        "verbose", REDIS_VERBOSE,
+        "notice", REDIS_NOTICE,
+        "warning", REDIS_WARNING,
+        NULL, REDIS_DEFAULT_VERBOSITY);
+    rewriteConfigStringOption(state,"logfile",server.logfile,REDIS_DEFAULT_LOGFILE);
+    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,REDIS_DEFAULT_SYSLOG_ENABLED);
+    rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,REDIS_DEFAULT_SYSLOG_IDENT);
+    rewriteConfigSyslogfacilityOption(state);
+    rewriteConfigSaveOption(state);
+    rewriteConfigNumericalOption(state,"databases",server.dbnum,REDIS_DEFAULT_DBNUM);
+    rewriteConfigYesNoOption(state,"stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err,REDIS_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR);
+    rewriteConfigYesNoOption(state,"rdbcompression",server.rdb_compression,REDIS_DEFAULT_RDB_COMPRESSION);
+    rewriteConfigYesNoOption(state,"rdbchecksum",server.rdb_checksum,REDIS_DEFAULT_RDB_CHECKSUM);
+    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,REDIS_DEFAULT_RDB_FILENAME);
+    rewriteConfigDirOption(state);
+    rewriteConfigSlaveofOption(state);
+    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
+    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,REDIS_DEFAULT_SLAVE_SERVE_STALE_DATA);
+    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,REDIS_DEFAULT_SLAVE_READ_ONLY);
+    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,REDIS_REPL_PING_SLAVE_PERIOD);
+    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,REDIS_REPL_TIMEOUT);
+    rewriteConfigBytesOption(state,"repl-backlog-size",server.repl_backlog_size,REDIS_DEFAULT_REPL_BACKLOG_SIZE);
+    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
+    rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
+    rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
+    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
+    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
+    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
+    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,
+        "volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU,
+        "allkeys-lru", REDIS_MAXMEMORY_ALLKEYS_LRU,
+        "volatile-random", REDIS_MAXMEMORY_VOLATILE_RANDOM,
+        "allkeys-random", REDIS_MAXMEMORY_ALLKEYS_RANDOM,
+        "volatile-ttl", REDIS_MAXMEMORY_VOLATILE_TTL,
+        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
+        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
+    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
+    rewriteConfigAppendonlyOption(state);
+    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
+        "everysec", AOF_FSYNC_EVERYSEC,
+        "always", AOF_FSYNC_ALWAYS,
+        "no", AOF_FSYNC_NO,
+        NULL, REDIS_DEFAULT_AOF_FSYNC);
+    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
+    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
+    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
+    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
+    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
+    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
+    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
+    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
+    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
+    rewriteConfigNotifykeyspaceeventsOption(state);
+    rewriteConfigNumericalOption(state,"hash-max-ziplist-entries",server.hash_max_ziplist_entries,REDIS_HASH_MAX_ZIPLIST_ENTRIES);
+    rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,REDIS_HASH_MAX_ZIPLIST_VALUE);
+    rewriteConfigNumericalOption(state,"list-max-ziplist-entries",server.list_max_ziplist_entries,REDIS_LIST_MAX_ZIPLIST_ENTRIES);
+    rewriteConfigNumericalOption(state,"list-max-ziplist-value",server.list_max_ziplist_value,REDIS_LIST_MAX_ZIPLIST_VALUE);
+    rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,REDIS_SET_MAX_INTSET_ENTRIES);
+    rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,REDIS_ZSET_MAX_ZIPLIST_ENTRIES);
+    rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,REDIS_ZSET_MAX_ZIPLIST_VALUE);
+    rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,REDIS_DEFAULT_ACTIVE_REHASHING);
+    rewriteConfigClientoutputbufferlimitOption(state);
+    rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
+    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
+
+    /* Step 3: remove all the orphaned lines in the old file, that is, lines
+     * that were used by a config option and are no longer used, like in case
+     * of multiple "save" options or duplicated options. */
+    rewriteConfigRemoveOrphaned(state);
+
+    /* Step 4: generate a new configuration file from the modified state
+     * and write it into the original file. */
+    newcontent = rewriteConfigGetContentFromState(state);
+    retval = rewriteConfigOverwriteFile(server.configfile,newcontent);
+
+    sdsfree(newcontent);
+    rewriteConfigReleaseState(state);
+    return retval;
+}
+
+/*-----------------------------------------------------------------------------
+ * CONFIG command entry point
+ *----------------------------------------------------------------------------*/
+
 void configCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc != 4) goto badarity;
@@ -1057,6 +1681,17 @@ void configCommand(redisClient *c) {
         server.aof_delayed_fsync = 0;
         resetCommandTableStats();
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"rewrite")) {
+        if (c->argc != 2) goto badarity;
+        if (server.configfile == NULL) {
+            addReplyError(c,"The server is running without a config file");
+            return;
+        }
+        if (rewriteConfig(server.configfile) == -1) {
+            addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
+        } else {
+            addReply(c,shared.ok);
+        }
     } else {
         addReplyError(c,
             "CONFIG subcommand must be one of GET, SET, RESETSTAT");