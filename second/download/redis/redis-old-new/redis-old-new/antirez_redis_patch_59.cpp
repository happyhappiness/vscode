@@ -57,7 +57,7 @@ int main(int argc, char **argv) {
     for (j = 0; j < 10; j++) {
         char buf[64];
 
-        snprintf(buf,64,"%d",j);
+        snprintf(buf,64,"%u",j);
         reply = redisCommand(c,"LPUSH mylist element-%s", buf);
         freeReplyObject(reply);
     }