@@ -9,7 +9,8 @@ int main(void) {
     redisContext *c;
     redisReply *reply;
 
-    c = redisConnect((char*)"127.0.0.1", 6379);
+    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
+    c = redisConnectWithTimeout((char*)"127.0.0.2", 6379, timeout);
     if (c->err) {
         printf("Connection error: %s\n", c->errstr);
         exit(1);