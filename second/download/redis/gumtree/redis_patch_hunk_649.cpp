 
     while(p < len)
         target[p++] = minval+rand()%(maxval-minval+1);
     return len;
 }
 
-void verify(unsigned char *zl, zlentry *e) {
-    int i;
+static void verify(unsigned char *zl, zlentry *e) {
     int len = ziplistLen(zl);
     zlentry _e;
 
-    for (i = 0; i < len; i++) {
+    ZIPLIST_ENTRY_ZERO(&_e);
+
+    for (int i = 0; i < len; i++) {
         memset(&e[i], 0, sizeof(zlentry));
-        e[i] = zipEntry(ziplistIndex(zl, i));
+        zipEntry(ziplistIndex(zl, i), &e[i]);
 
         memset(&_e, 0, sizeof(zlentry));
-        _e = zipEntry(ziplistIndex(zl, -len+i));
+        zipEntry(ziplistIndex(zl, -len+i), &_e);
 
         assert(memcmp(&e[i], &_e, sizeof(zlentry)) == 0);
     }
 }
 
-int main(int argc, char **argv) {
+int ziplistTest(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
     unsigned int elen;
     long long value;
 
     /* If an argument is given, use it as the random seed. */
     if (argc == 2)
         srand(atoi(argv[1]));
 
     zl = createIntList();
     ziplistRepr(zl);
 
+    zfree(zl);
+
     zl = createList();
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_HEAD);
+    zl = pop(zl,ZIPLIST_HEAD);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
-    pop(zl,ZIPLIST_TAIL);
+    zl = pop(zl,ZIPLIST_TAIL);
     ziplistRepr(zl);
 
+    zfree(zl);
+
     printf("Get element at index 3:\n");
     {
         zl = createList();
         p = ziplistIndex(zl, 3);
         if (!ziplistGet(p, &entry, &elen, &value)) {
             printf("ERROR: Could not access index 3\n");
