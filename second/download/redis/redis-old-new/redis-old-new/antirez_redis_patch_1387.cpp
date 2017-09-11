@@ -478,7 +478,7 @@ static sds cliFormatReplyCSV(redisReply *r) {
 static int cliReadReply(int output_raw_strings) {
     void *_reply;
     redisReply *reply;
-    sds out;
+    sds out = NULL;
     int output = 1;
 
     if (redisGetReply(context,&_reply) != REDIS_OK) {
@@ -498,7 +498,8 @@ static int cliReadReply(int output_raw_strings) {
 
     reply = (redisReply*)_reply;
 
-    /* Check if we need to connect to a different node and reissue the request. */
+    /* Check if we need to connect to a different node and reissue the
+     * request. */
     if (config.cluster_mode && reply->type == REDIS_REPLY_ERROR &&
         (!strncmp(reply->str,"MOVED",5) || !strcmp(reply->str,"ASK")))
     {
@@ -926,7 +927,10 @@ static void slaveMode(void) {
     unsigned long long payload;
 
     /* Send the SYNC command. */
-    write(fd,"SYNC\r\n",6);
+    if (write(fd,"SYNC\r\n",6) != 6) {
+        fprintf(stderr,"Error writing to master\n");
+        exit(1);
+    }
 
     /* Read $<payload>\r\n, making sure to read just up to "\n" */
     p = buf;