@@ -34,7 +34,7 @@
 #define D(...)                                                               \
     do {                                                                     \
         FILE *fp = fopen("/tmp/log.txt","a");                                \
-        fprintf(fp,"%s:%s:%d:\t", __FILE__, __FUNCTION__, __LINE__);         \
+        fprintf(fp,"%s:%s:%d:\t", __FILE__, __func__, __LINE__);             \
         fprintf(fp,__VA_ARGS__);                                             \
         fprintf(fp,"\n");                                                    \
         fclose(fp);                                                          \