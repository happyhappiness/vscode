@@ -263,11 +263,9 @@ static int cliAuth() {
 /* Send SELECT dbnum to the server */
 static int cliSelect() {
     redisReply *reply;
-    char dbnum[16];
     if (config.dbnum == 0) return REDIS_OK;
 
-    snprintf(dbnum,sizeof(dbnum),"%d",config.dbnum);
-    reply = redisCommand(context,"SELECT %s",dbnum);
+    reply = redisCommand(context,"SELECT %d",config.dbnum);
     if (reply != NULL) {
         freeReplyObject(reply);
         return REDIS_OK;
@@ -491,6 +489,10 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
         if (cliReadReply(output_raw) != REDIS_OK) {
             free(argvlen);
             return REDIS_ERR;
+        } else {
+            /* Store database number when SELECT was successfully executed. */
+            if (!strcasecmp(command,"select") && argc == 2)
+                config.dbnum = atoi(argv[1]);
         }
     }
 