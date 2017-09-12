@@ -107,6 +107,30 @@ unsigned char *ziplistPop(unsigned char *zl, sds *value, int where) {
     return zl;
 }
 
+/* Returns an offset to use for iterating with ziplistNext. */
+unsigned char *ziplistIndex(unsigned char *zl, unsigned int index) {
+    unsigned char *p = zl+ZIPLIST_HEADER_SIZE;
+    unsigned int i = 0;
+    for (; i < index; i++) {
+        if (*p == ZIP_END) break;
+        p += zipRawEntryLength(p);
+    }
+    return p;
+}
+
+/* Store entry at current position in sds *value and return pointer
+ * to the next entry. */
+unsigned char *ziplistNext(unsigned char *p, sds *value) {
+    if (*p == ZIP_END) return NULL;
+    if (value) {
+        unsigned int len;
+        len = zipDecodeLength(p);
+        *value = sdsnewlen(p+zipEncodeLength(NULL,len),len);
+    }
+    p += zipRawEntryLength(p);
+    return p;
+}
+
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p;
     unsigned int l;
@@ -125,16 +149,20 @@ void ziplistRepr(unsigned char *zl) {
 }
 
 #ifdef ZIPLIST_TEST_MAIN
-int main(int argc, char **argv) {
-    unsigned char *zl;
-    sds s;
 
-    zl = ziplistNew();
+unsigned char *createList() {
+    unsigned char *zl = ziplistNew();
     zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
-    ziplistRepr(zl);
     zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
-    ziplistRepr(zl);
     zl = ziplistPush(zl, (unsigned char*)"hello", 5, ZIPLIST_HEAD);
+    return zl;
+}
+
+int main(int argc, char **argv) {
+    unsigned char *zl, *p;
+    sds s;
+
+    zl = createList();
     ziplistRepr(zl);
 
     zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
@@ -145,6 +173,47 @@ int main(int argc, char **argv) {
     printf("Pop head: %s (length %ld)\n", s, sdslen(s));
     ziplistRepr(zl);
 
+    printf("Iterate list from 0 to end:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 0);
+        while ((p = ziplistNext(p, &s)) != NULL) {
+            printf("Entry: %s (length %ld)\n", s, sdslen(s));
+        }
+        printf("\n");
+    }
+
+    printf("Iterate list from 1 to end:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 1);
+        while ((p = ziplistNext(p, &s)) != NULL) {
+            printf("Entry: %s (length %ld)\n", s, sdslen(s));
+        }
+        printf("\n");
+    }
+
+    printf("Iterate list from 2 to end:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 2);
+        while ((p = ziplistNext(p, &s)) != NULL) {
+            printf("Entry: %s (length %ld)\n", s, sdslen(s));
+        }
+        printf("\n");
+    }
+
+    printf("Iterate starting out of range:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 3);
+        if (ziplistNext(p, &s) == NULL) {
+            printf("No entry\n");
+        } else {
+            printf("ERROR\n");
+        }
+    }
+
     return 0;
 }
 #endif