         printf("\n");
         freeReplyObject(reply);
         usleep(config.interval);
     }
 }
 
+/*------------------------------------------------------------------------------
+ * Scan mode
+ *--------------------------------------------------------------------------- */
+
 static void scanMode() {
     redisReply *reply;
     unsigned long long cur = 0;
 
     do {
         if (config.pattern)
