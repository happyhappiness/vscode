@@ -15,15 +15,20 @@ void getCallback(redisAsyncContext *c, void *r, void *privdata) {
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
     signal(SIGPIPE, SIG_IGN);
-    struct ev_loop *loop = ev_default_loop(0);
 
     redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
     if (c->err) {
@@ -32,10 +37,11 @@ int main (int argc, char **argv) {
         return 1;
     }
 
-    redisLibevAttach(c,loop);
+    redisLibevAttach(EV_DEFAULT_ c);
+    redisAsyncSetConnectCallback(c,connectCallback);
     redisAsyncSetDisconnectCallback(c,disconnectCallback);
     redisAsyncCommand(c, NULL, NULL, "SET key %b", argv[argc-1], strlen(argv[argc-1]));
     redisAsyncCommand(c, getCallback, (char*)"end-1", "GET key");
-    ev_loop(loop, 0);
+    ev_loop(EV_DEFAULT_ 0);
     return 0;
 }