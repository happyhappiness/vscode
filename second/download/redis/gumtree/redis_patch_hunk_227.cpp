     int i = 0;
 
     while(1) {
         char buf[64];
         int j;
 
-        reply = reconnectingInfo();
+        reply = reconnectingRedisCommand(context,"INFO");
         if (reply->type == REDIS_REPLY_ERROR) {
             printf("ERROR: %s\n", reply->str);
             exit(1);
         }
 
         if ((i++ % 20) == 0) {
