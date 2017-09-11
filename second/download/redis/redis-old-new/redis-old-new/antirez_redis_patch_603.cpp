@@ -702,29 +702,33 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     return REDIS_OK;
 }
 
-/* Send the INFO command, reconnecting the link if needed. */
-static redisReply *reconnectingInfo(void) {
-    redisContext *c = context;
+/* Send a command reconnecting the link if needed. */
+static redisReply *reconnectingRedisCommand(redisContext *c, const char *fmt, ...) {
     redisReply *reply = NULL;
     int tries = 0;
+    va_list ap;
 
     assert(!c->err);
     while(reply == NULL) {
         while (c->err & (REDIS_ERR_IO | REDIS_ERR_EOF)) {
-            printf("Reconnecting (%d)...\r", ++tries);
+            printf("\r\x1b[0K"); /* Cursor to left edge + clear line. */
+            printf("Reconnecting... %d\r", ++tries);
             fflush(stdout);
 
             redisFree(c);
             c = redisConnect(config.hostip,config.hostport);
             usleep(1000000);
         }
 
-        reply = redisCommand(c,"INFO");
+        va_start(ap,fmt);
+        reply = redisvCommand(c,fmt,ap);
+        va_end(ap);
+
         if (c->err && !(c->err & (REDIS_ERR_IO | REDIS_ERR_EOF))) {
             fprintf(stderr, "Error: %s\n", c->errstr);
             exit(1);
         } else if (tries > 0) {
-            printf("\n");
+            printf("\r\x1b[0K"); /* Cursor to left edge + clear line. */
         }
     }
 
@@ -1083,7 +1087,7 @@ static void latencyMode(void) {
     if (!context) exit(1);
     while(1) {
         start = mstime();
-        reply = redisCommand(context,"PING");
+        reply = reconnectingRedisCommand(context,"PING");
         if (reply == NULL) {
             fprintf(stderr,"\nI/O error\n");
             exit(1);
@@ -1233,7 +1237,7 @@ static void latencyDistMode(void) {
     if (!context) exit(1);
     while(1) {
         start = ustime();
-        reply = redisCommand(context,"PING");
+        reply = reconnectingRedisCommand(context,"PING");
         if (reply == NULL) {
             fprintf(stderr,"\nI/O error\n");
             exit(1);
@@ -1881,7 +1885,7 @@ static void statMode(void) {
         char buf[64];
         int j;
 
-        reply = reconnectingInfo();
+        reply = reconnectingRedisCommand(context,"INFO");
         if (reply->type == REDIS_REPLY_ERROR) {
             printf("ERROR: %s\n", reply->str);
             exit(1);