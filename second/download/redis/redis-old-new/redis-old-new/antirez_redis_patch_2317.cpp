@@ -975,15 +975,20 @@ static int yesnotoi(char *s) {
 /* I agree, this is a very rudimental way to load a configuration...
    will improve later if the config gets more complex */
 static void loadServerConfig(char *filename) {
-    FILE *fp = fopen(filename,"r");
+    FILE *fp;
     char buf[REDIS_CONFIGLINE_MAX+1], *err = NULL;
     int linenum = 0;
     sds line = NULL;
-    
-    if (!fp) {
-        redisLog(REDIS_WARNING,"Fatal error, can't open config file");
-        exit(1);
+
+    if (filename[0] == '-' && filename[1] == '\0')
+        fp = stdin;
+    else {
+        if ((fp = fopen(filename,"r")) == NULL) {
+            redisLog(REDIS_WARNING,"Fatal error, can't open config file");
+            exit(1);
+        }
     }
+
     while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL) {
         sds *argv;
         int argc, j;
@@ -1037,7 +1042,7 @@ static void loadServerConfig(char *filename) {
                 goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
-            FILE *fp;
+            FILE *logfp;
 
             server.logfile = zstrdup(argv[1]);
             if (!strcasecmp(server.logfile,"stdout")) {
@@ -1047,13 +1052,13 @@ static void loadServerConfig(char *filename) {
             if (server.logfile) {
                 /* Test if we are able to open the file. The server will not
                  * be able to abort just for this problem later... */
-                fp = fopen(server.logfile,"a");
-                if (fp == NULL) {
+                logfp = fopen(server.logfile,"a");
+                if (logfp == NULL) {
                     err = sdscatprintf(sdsempty(),
                         "Can't open the log file: %s", strerror(errno));
                     goto loaderr;
                 }
-                fclose(fp);
+                fclose(logfp);
             }
         } else if (!strcasecmp(argv[0],"databases") && argc == 2) {
             server.dbnum = atoi(argv[1]);
@@ -1099,7 +1104,7 @@ static void loadServerConfig(char *filename) {
         zfree(argv);
         sdsfree(line);
     }
-    fclose(fp);
+    if (fp != stdin) fclose(fp);
     return;
 
 loaderr: