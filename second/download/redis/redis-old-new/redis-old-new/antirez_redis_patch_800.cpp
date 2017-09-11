@@ -94,6 +94,7 @@ static struct config {
     sds mb_delim;
     char prompt[128];
     char *eval;
+    int last_cmd_type;
 } config;
 
 static volatile sig_atomic_t force_cancel_loop = 0;
@@ -131,7 +132,7 @@ static void cliRefreshPrompt(void) {
                        strchr(config.hostip,':') ? "[%s]:%d" : "%s:%d",
                        config.hostip, config.hostport);
     /* Add [dbnum] if needed */
-    if (config.dbnum != 0)
+    if (config.dbnum != 0 && config.last_cmd_type != REDIS_REPLY_ERROR)
         len += snprintf(config.prompt+len,sizeof(config.prompt)-len,"[%d]",
             config.dbnum);
     snprintf(config.prompt+len,sizeof(config.prompt)-len,"> ");
@@ -532,6 +533,8 @@ static int cliReadReply(int output_raw_strings) {
 
     reply = (redisReply*)_reply;
 
+    config.last_cmd_type = reply->type;
+
     /* Check if we need to connect to a different node and reissue the
      * request. */
     if (config.cluster_mode && reply->type == REDIS_REPLY_ERROR &&
@@ -1887,6 +1890,8 @@ int main(int argc, char **argv) {
     config.stdinarg = 0;
     config.auth = NULL;
     config.eval = NULL;
+    config.last_cmd_type = -1;
+
     if (!isatty(fileno(stdout)) && (getenv("FAKETTY") == NULL))
         config.output = OUTPUT_RAW;
     else