@@ -926,44 +926,44 @@ static void loadServerConfig(char *filename) {
         sdstolower(argv[0]);
 
         /* Execute config directives */
-        if (!strcmp(argv[0],"timeout") && argc == 2) {
+        if (!strcasecmp(argv[0],"timeout") && argc == 2) {
             server.maxidletime = atoi(argv[1]);
             if (server.maxidletime < 1) {
                 err = "Invalid timeout value"; goto loaderr;
             }
-        } else if (!strcmp(argv[0],"port") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"port") && argc == 2) {
             server.port = atoi(argv[1]);
             if (server.port < 1 || server.port > 65535) {
                 err = "Invalid port"; goto loaderr;
             }
-        } else if (!strcmp(argv[0],"bind") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"bind") && argc == 2) {
             server.bindaddr = zstrdup(argv[1]);
-        } else if (!strcmp(argv[0],"save") && argc == 3) {
+        } else if (!strcasecmp(argv[0],"save") && argc == 3) {
             int seconds = atoi(argv[1]);
             int changes = atoi(argv[2]);
             if (seconds < 1 || changes < 0) {
                 err = "Invalid save parameters"; goto loaderr;
             }
             appendServerSaveParams(seconds,changes);
-        } else if (!strcmp(argv[0],"dir") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"dir") && argc == 2) {
             if (chdir(argv[1]) == -1) {
                 redisLog(REDIS_WARNING,"Can't chdir to '%s': %s",
                     argv[1], strerror(errno));
                 exit(1);
             }
-        } else if (!strcmp(argv[0],"loglevel") && argc == 2) {
-            if (!strcmp(argv[1],"debug")) server.verbosity = REDIS_DEBUG;
-            else if (!strcmp(argv[1],"notice")) server.verbosity = REDIS_NOTICE;
-            else if (!strcmp(argv[1],"warning")) server.verbosity = REDIS_WARNING;
+        } else if (!strcasecmp(argv[0],"loglevel") && argc == 2) {
+            if (!strcasecmp(argv[1],"debug")) server.verbosity = REDIS_DEBUG;
+            else if (!strcasecmp(argv[1],"notice")) server.verbosity = REDIS_NOTICE;
+            else if (!strcasecmp(argv[1],"warning")) server.verbosity = REDIS_WARNING;
             else {
                 err = "Invalid log level. Must be one of debug, notice, warning";
                 goto loaderr;
             }
-        } else if (!strcmp(argv[0],"logfile") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
             FILE *fp;
 
             server.logfile = zstrdup(argv[1]);
-            if (!strcmp(server.logfile,"stdout")) {
+            if (!strcasecmp(server.logfile,"stdout")) {
                 zfree(server.logfile);
                 server.logfile = NULL;
             }
@@ -978,32 +978,32 @@ static void loadServerConfig(char *filename) {
                 }
                 fclose(fp);
             }
-        } else if (!strcmp(argv[0],"databases") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"databases") && argc == 2) {
             server.dbnum = atoi(argv[1]);
             if (server.dbnum < 1) {
                 err = "Invalid number of databases"; goto loaderr;
             }
-        } else if (!strcmp(argv[0],"slaveof") && argc == 3) {
+        } else if (!strcasecmp(argv[0],"slaveof") && argc == 3) {
             server.masterhost = sdsnew(argv[1]);
             server.masterport = atoi(argv[2]);
             server.replstate = REDIS_REPL_CONNECT;
-        } else if (!strcmp(argv[0],"glueoutputbuf") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"glueoutputbuf") && argc == 2) {
             if ((server.glueoutputbuf = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
-        } else if (!strcmp(argv[0],"shareobjects") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"shareobjects") && argc == 2) {
             if ((server.shareobjects = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
-        } else if (!strcmp(argv[0],"daemonize") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"daemonize") && argc == 2) {
             if ((server.daemonize = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
-        } else if (!strcmp(argv[0],"requirepass") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
           server.requirepass = zstrdup(argv[1]);
-        } else if (!strcmp(argv[0],"pidfile") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"pidfile") && argc == 2) {
           server.pidfile = zstrdup(argv[1]);
-        } else if (!strcmp(argv[0],"dbfilename") && argc == 2) {
+        } else if (!strcasecmp(argv[0],"dbfilename") && argc == 2) {
           server.dbfilename = zstrdup(argv[1]);
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
@@ -1140,7 +1140,7 @@ static void sendReplyToClient(aeEventLoop *el, int fd, void *privdata, int mask)
 static struct redisCommand *lookupCommand(char *name) {
     int j = 0;
     while(cmdTable[j].name != NULL) {
-        if (!strcmp(name,cmdTable[j].name)) return &cmdTable[j];
+        if (!strcasecmp(name,cmdTable[j].name)) return &cmdTable[j];
         j++;
     }
     return NULL;
@@ -1164,10 +1164,9 @@ static int processCommand(redisClient *c) {
     struct redisCommand *cmd;
     long long dirty;
 
-    sdstolower(c->argv[0]->ptr);
     /* The QUIT command is handled as a special case. Normal command
      * procs are unable to close the client connection safely */
-    if (!strcmp(c->argv[0]->ptr,"quit")) {
+    if (!strcasecmp(c->argv[0]->ptr,"quit")) {
         freeClient(c);
         return 0;
     }