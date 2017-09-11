@@ -87,9 +87,11 @@ static long long mstime(void) {
 
 static void cliRefreshPrompt(void) {
     if (config.dbnum == 0)
-        snprintf(config.prompt,sizeof(config.prompt),"redis> ");
+        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d> ",
+            config.hostip, config.hostport);
     else
-        snprintf(config.prompt,sizeof(config.prompt),"redis:%d> ",config.dbnum);
+        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d[%d]> ",
+            config.hostip, config.hostport, config.dbnum);
 }
 
 /*------------------------------------------------------------------------------
@@ -314,10 +316,9 @@ static int cliConnect(int force) {
     return REDIS_OK;
 }
 
-static void cliPrintContextErrorAndExit() {
+static void cliPrintContextError() {
     if (context == NULL) return;
     fprintf(stderr,"Error: %s\n",context->errstr);
-    exit(1);
 }
 
 static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
@@ -436,7 +437,8 @@ static int cliReadReply(int output_raw_strings) {
             if (context->err == REDIS_ERR_EOF)
                 return REDIS_ERR;
         }
-        cliPrintContextErrorAndExit();
+        cliPrintContextError();
+        exit(1);
         return REDIS_ERR; /* avoid compiler warning */
     }
 
@@ -462,10 +464,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     size_t *argvlen;
     int j, output_raw;
 
-    if (context == NULL) {
-        printf("Not connected, please use: connect <host> <port>\n");
-        return REDIS_OK;
-    }
+    if (context == NULL) return REDIS_ERR;
 
     output_raw = 0;
     if (!strcasecmp(command,"info") ||
@@ -688,7 +687,7 @@ static void repl() {
                         /* If we still cannot send the command,
                          * print error and abort. */
                         if (cliSendCommand(argc,argv,1) != REDIS_OK)
-                            cliPrintContextErrorAndExit();
+                            cliPrintContextError();
                     }
                     elapsed = mstime()-start_time;
                     if (elapsed >= 500) {
@@ -741,11 +740,15 @@ int main(int argc, char **argv) {
     argc -= firstarg;
     argv += firstarg;
 
-    /* Try to connect */
-    if (cliConnect(0) != REDIS_OK) exit(1);
-
     /* Start interactive mode when no command is provided */
-    if (argc == 0) repl();
+    if (argc == 0) {
+        /* Note that in repl mode we don't abort on connection error.
+         * A new attempt will be performed for every command send. */
+        cliConnect(0);
+        repl();
+    }
+
     /* Otherwise, we have some arguments to execute */
+    if (cliConnect(0) != REDIS_OK) exit(1);
     return noninteractive(argc,convertToSds(argc,argv));
 }