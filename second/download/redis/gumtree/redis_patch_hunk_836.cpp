 
 void serverLogHexDump(int level, char *descr, void *value, size_t len) {
     char buf[65], *b;
     unsigned char *v = value;
     char charset[] = "0123456789abcdef";
 
-    serverLog(level,"%s (hexdump):", descr);
+    serverLog(level,"%s (hexdump of %zu bytes):", descr, len);
     b = buf;
     while(len) {
         b[0] = charset[(*v)>>4];
         b[1] = charset[(*v)&0xf];
         b[2] = '\0';
         b += 2;
