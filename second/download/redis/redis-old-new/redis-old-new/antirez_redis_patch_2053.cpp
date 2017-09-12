@@ -584,10 +584,10 @@ void ziplistRepr(unsigned char *zl) {
 
 unsigned char *createList() {
     unsigned char *zl = ziplistNew();
-    zl = ziplistPush(zl, "foo", 3, ZIPLIST_TAIL);
-    zl = ziplistPush(zl, "quux", 4, ZIPLIST_TAIL);
-    zl = ziplistPush(zl, "hello", 5, ZIPLIST_HEAD);
-    zl = ziplistPush(zl, "1024", 4, ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)"hello", 5, ZIPLIST_HEAD);
+    zl = ziplistPush(zl, (unsigned char*)"1024", 4, ZIPLIST_TAIL);
     return zl;
 }
 
@@ -596,23 +596,23 @@ unsigned char *createIntList() {
     char buf[32];
 
     sprintf(buf, "100");
-    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_TAIL);
     sprintf(buf, "128000");
-    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_TAIL);
     sprintf(buf, "-100");
-    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_HEAD);
+    zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_HEAD);
     sprintf(buf, "4294967296");
-    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_HEAD);
+    zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_HEAD);
     sprintf(buf, "non integer");
-    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_TAIL);
     sprintf(buf, "much much longer non integer");
-    zl = ziplistPush(zl, buf, strlen(buf), ZIPLIST_TAIL);
+    zl = ziplistPush(zl, (unsigned char*)buf, strlen(buf), ZIPLIST_TAIL);
     return zl;
 }
 
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
-    char *entry;
+    unsigned char *entry;
     unsigned int elen;
     long long value;
     sds s;
@@ -852,19 +852,19 @@ int main(int argc, char **argv) {
     printf("Delete foo while iterating:\n");
     {
         zl = createList();
-        p = ziplistIndex(zl, 0);
-        while (ziplistGet(p, &entry, &elen, &value)) {
-            if (entry && strncmp("foo", entry, elen) == 0) {
+        p = ziplistIndex(zl,0);
+        while (ziplistGet(p,&entry,&elen,&value)) {
+            if (entry && strncmp("foo",(char*)entry,elen) == 0) {
                 printf("Delete foo\n");
-                zl = ziplistDelete(zl, &p, ZIPLIST_TAIL);
+                zl = ziplistDelete(zl,&p);
             } else {
                 printf("Entry: ");
                 if (entry) {
                     fwrite(entry,elen,1,stdout);
                 } else {
-                    printf("%lld", value);
+                    printf("%lld",value);
                 }
-                p = ziplistNext(p);
+                p = ziplistNext(zl,p);
                 printf("\n");
             }
         }
@@ -879,7 +879,7 @@ int main(int argc, char **argv) {
         int i,len;
         for (i = 0; i < 1000; i++) {
             len = sprintf(buf,"%d",i);
-            zl = ziplistPush(zl,buf,len,ZIPLIST_TAIL);
+            zl = ziplistPush(zl,(unsigned char*)buf,len,ZIPLIST_TAIL);
         }
         for (i = 0; i < 1000; i++) {
             p = ziplistIndex(zl,i);
@@ -896,22 +896,22 @@ int main(int argc, char **argv) {
     printf("Compare strings with ziplist entries:\n");
     {
         zl = createList();
-        p = ziplistIndex(zl, 0);
-        if (!ziplistCompare(p,"hello",5)) {
+        p = ziplistIndex(zl,0);
+        if (!ziplistCompare(p,(unsigned char*)"hello",5)) {
             printf("ERROR: not \"hello\"\n");
             return 1;
         }
-        if (ziplistCompare(p,"hella",5)) {
+        if (ziplistCompare(p,(unsigned char*)"hella",5)) {
             printf("ERROR: \"hella\"\n");
             return 1;
         }
 
-        p = ziplistIndex(zl, 3);
-        if (!ziplistCompare(p,"1024",4)) {
+        p = ziplistIndex(zl,3);
+        if (!ziplistCompare(p,(unsigned char*)"1024",4)) {
             printf("ERROR: not \"1024\"\n");
             return 1;
         }
-        if (ziplistCompare(p,"1025",4)) {
+        if (ziplistCompare(p,(unsigned char*)"1025",4)) {
             printf("ERROR: \"1025\"\n");
             return 1;
         }