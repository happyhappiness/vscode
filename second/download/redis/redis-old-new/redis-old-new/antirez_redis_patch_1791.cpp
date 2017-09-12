@@ -195,6 +195,11 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
             exit(1);
         }
         if (reply != NULL) {
+            if (reply == (void*)REDIS_REPLY_ERROR) {
+                fprintf(stderr,"Unexpected error reply, exiting...\n");
+                exit(1);
+            }
+
             if (config.donerequests < config.requests)
                 config.latency[config.donerequests++] = c->latency;
             clientDone(c);
@@ -454,8 +459,9 @@ int main(int argc, char **argv) {
         c->obuf = sdscatprintf(c->obuf,"*%d\r\n$4\r\nMSET\r\n", 11);
         {
             int i;
-            char *data = zmalloc(config.datasize+2);
+            char *data = zmalloc(config.datasize+1);
             memset(data,'x',config.datasize);
+            data[config.datasize] = '\0';
             for (i = 0; i < 10; i++) {
                 c->obuf = sdscatprintf(c->obuf,"$%d\r\n%s\r\n",config.datasize,data);
             }