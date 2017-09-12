@@ -17,7 +17,7 @@ int main(void) {
 
     /* PING server */
     reply = redisCommand(c,"PING");
-    printf("PONG: %s\n", reply->str);
+    printf("PING: %s\n", reply->str);
     freeReplyObject(reply);
 
     /* Set a key */