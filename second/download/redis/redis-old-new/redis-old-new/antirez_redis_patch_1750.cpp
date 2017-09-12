@@ -15,10 +15,16 @@ void getCallback(redisAsyncContext *c, void *r, void *privdata) {
     redisAsyncDisconnect(c);
 }
 
+void connectCallback(const redisAsyncContext *c) {
+    ((void)c);
+    printf("connected...\n");
+}
+
 void disconnectCallback(const redisAsyncContext *c, int status) {
     if (status != REDIS_OK) {
         printf("Error: %s\n", c->errstr);
     }
+    printf("disconnected...\n");
 }
 
 int main (int argc, char **argv) {
@@ -33,6 +39,7 @@ int main (int argc, char **argv) {
     }
 
     redisLibeventAttach(c,base);
+    redisAsyncSetConnectCallback(c,connectCallback);
     redisAsyncSetDisconnectCallback(c,disconnectCallback);
     redisAsyncCommand(c, NULL, NULL, "SET key %b", argv[argc-1], strlen(argv[argc-1]));
     redisAsyncCommand(c, getCallback, (char*)"end-1", "GET key");