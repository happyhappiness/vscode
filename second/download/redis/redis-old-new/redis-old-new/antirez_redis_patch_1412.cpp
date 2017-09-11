@@ -15,16 +15,20 @@ void getCallback(redisAsyncContext *c, void *r, void *privdata) {
     redisAsyncDisconnect(c);
 }
 
-void connectCallback(const redisAsyncContext *c) {
-    ((void)c);
-    printf("connected...\n");
+void connectCallback(const redisAsyncContext *c, int status) {
+    if (status != REDIS_OK) {
+        printf("Error: %s\n", c->errstr);
+        return;
+    }
+    printf("Connected...\n");
 }
 
 void disconnectCallback(const redisAsyncContext *c, int status) {
     if (status != REDIS_OK) {
         printf("Error: %s\n", c->errstr);
+        return;
     }
-    printf("disconnected...\n");
+    printf("Disconnected...\n");
 }
 
 int main (int argc, char **argv) {