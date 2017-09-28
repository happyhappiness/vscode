         p += entry.len;
         index++;
     }
     printf("{end}\n\n");
 }
 
-#ifdef ZIPLIST_TEST_MAIN
+#ifdef REDIS_TEST
 #include <sys/time.h>
 #include "adlist.h"
 #include "sds.h"
 
 #define debug(f, ...) { if (DEBUG) printf(f, __VA_ARGS__); }
 
-unsigned char *createList() {
+static unsigned char *createList() {
     unsigned char *zl = ziplistNew();
     zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
     zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
     zl = ziplistPush(zl, (unsigned char*)"hello", 5, ZIPLIST_HEAD);
     zl = ziplistPush(zl, (unsigned char*)"1024", 4, ZIPLIST_TAIL);
     return zl;
 }
 
-unsigned char *createIntList() {
+static unsigned char *createIntList() {
     unsigned char *zl = ziplistNew();
     char buf[32];
 
     sprintf(buf, "100");
     zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_TAIL);
     sprintf(buf, "128000");
