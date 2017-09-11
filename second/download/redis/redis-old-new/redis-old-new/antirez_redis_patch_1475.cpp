@@ -23,39 +23,25 @@ void resetServerSaveParams() {
     server.saveparamslen = 0;
 }
 
-/* I agree, this is a very rudimental way to load a configuration...
-   will improve later if the config gets more complex */
-void loadServerConfig(char *filename) {
-    FILE *fp;
-    char buf[REDIS_CONFIGLINE_MAX+1], *err = NULL;
-    int linenum = 0;
-    sds line = NULL;
-
-    if (filename[0] == '-' && filename[1] == '\0')
-        fp = stdin;
-    else {
-        if ((fp = fopen(filename,"r")) == NULL) {
-            redisLog(REDIS_WARNING, "Fatal error, can't open config file '%s'", filename);
-            exit(1);
-        }
-    }
+void loadServerConfigFromString(char *config) {
+    char *err = NULL;
+    int linenum = 0, totlines, i;
+    sds *lines;
+
+    lines = sdssplitlen(config,strlen(config),"\n",1,&totlines);
 
-    while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL) {
+    for (i = 0; i < totlines; i++) {
         sds *argv;
-        int argc, j;
+        int argc;
 
-        linenum++;
-        line = sdsnew(buf);
-        line = sdstrim(line," \t\r\n");
+        linenum = i+1;
+        lines[i] = sdstrim(lines[i]," \t\r\n");
 
         /* Skip comments and blank lines*/
-        if (line[0] == '#' || line[0] == '\0') {
-            sdsfree(line);
-            continue;
-        }
+        if (lines[i][0] == '#' || lines[i][0] == '\0') continue;
 
         /* Split into arguments */
-        argv = sdssplitargs(line,&argc);
+        argv = sdssplitargs(lines[i],&argc);
         sdstolower(argv[0]);
 
         /* Execute config directives */
@@ -162,7 +148,7 @@ void loadServerConfig(char *filename) {
                 err = "Invalid number of databases"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"include") && argc == 2) {
-            loadServerConfig(argv[1]);
+            loadServerConfig(argv[1],NULL);
         } else if (!strcasecmp(argv[0],"maxclients") && argc == 2) {
             server.maxclients = atoi(argv[1]);
         } else if (!strcasecmp(argv[0],"maxmemory") && argc == 2) {
@@ -325,22 +311,56 @@ void loadServerConfig(char *filename) {
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
-        for (j = 0; j < argc; j++)
-            sdsfree(argv[j]);
-        zfree(argv);
-        sdsfree(line);
+        sdsfreesplitres(argv,argc);
     }
-    if (fp != stdin) fclose(fp);
+    sdsfreesplitres(lines,totlines);
     return;
 
 loaderr:
     fprintf(stderr, "\n*** FATAL CONFIG FILE ERROR ***\n");
     fprintf(stderr, "Reading the configuration file, at line %d\n", linenum);
-    fprintf(stderr, ">>> '%s'\n", line);
+    fprintf(stderr, ">>> '%s'\n", lines[i]);
     fprintf(stderr, "%s\n", err);
     exit(1);
 }
 
+/* Load the server configuration from the specified filename.
+ * The function appends the additional configuration directives stored
+ * in the 'options' string to the config file before loading.
+ *
+ * Both filename and options can be NULL, in such a case are considered
+ * emtpy. This way loadServerConfig can be used to just load a file or
+ * just load a string. */
+void loadServerConfig(char *filename, char *options) {
+    sds config = sdsempty();
+    char buf[REDIS_CONFIGLINE_MAX+1];
+
+    /* Load the file content */
+    if (filename) {
+        FILE *fp;
+
+        if (filename[0] == '-' && filename[1] == '\0') {
+            fp = stdin;
+        } else {
+            if ((fp = fopen(filename,"r")) == NULL) {
+                redisLog(REDIS_WARNING,
+                    "Fatal error, can't open config file '%s'", filename);
+                exit(1);
+            }
+        }
+        while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL)
+            config = sdscat(config,buf);
+        if (fp != stdin) fclose(fp);
+    }
+    /* Append the additional options */
+    if (options) {
+        config = sdscat(config,"\n");
+        config = sdscat(config,options);
+    }
+    loadServerConfigFromString(config);
+    sdsfree(config);
+}
+
 /*-----------------------------------------------------------------------------
  * CONFIG command for remote configuration
  *----------------------------------------------------------------------------*/