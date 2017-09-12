@@ -296,18 +296,31 @@ unsigned char *ziplistIndex(unsigned char *zl, unsigned int index) {
     return p;
 }
 
-/* Store entry at current position in sds *value and return pointer
- * to the next entry. */
-unsigned char *ziplistNext(unsigned char *p, unsigned char **q, unsigned char **entry, unsigned int *elen) {
-    unsigned int lensize;
-    if (*p == ZIP_END) return NULL;
-    if (entry) {
-        *elen = zipDecodeLength(p,&lensize);
-        *entry = p+lensize;
+/* Return pointer to next entry in ziplist. */
+unsigned char *ziplistNext(unsigned char *p) {
+    return *p == ZIP_END ? p : p+zipRawEntryLength(p);
+}
+
+/* Get entry pointer to by 'p' and store in either 'e' or 'v' depending
+ * on the encoding of the entry. 'e' is always set to NULL to be able
+ * to find out whether the string pointer or the integer value was set.
+ * Return 0 if 'p' points to the end of the zipmap, 1 otherwise. */
+unsigned int ziplistGet(unsigned char *p, unsigned char **e, unsigned int *elen, long long *v) {
+    unsigned int len, lensize;
+    if (*p == ZIP_END) return 0;
+    if (e) *e = NULL;
+    len = zipDecodeLength(p,&lensize);
+    if (ZIP_ENCODING(p) == ZIP_ENC_RAW) {
+        if (e) {
+            *elen = len;
+            *e = p+lensize;
+        }
+    } else {
+        if (v) {
+            *v = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
+        }
     }
-    if (q != NULL) *q = p;
-    p += zipRawEntryLength(p);
-    return p;
+    return 1;
 }
 
 /* Delete a range of entries from the ziplist. */
@@ -382,6 +395,7 @@ unsigned char *createList() {
     zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
     zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
     zl = ziplistPush(zl, (unsigned char*)"hello", 5, ZIPLIST_HEAD);
+    zl = ziplistPush(zl, (unsigned char*)"1024", 4, ZIPLIST_TAIL);
     return zl;
 }
 
@@ -407,6 +421,7 @@ unsigned char *createIntList() {
 int main(int argc, char **argv) {
     unsigned char *zl, *p, *q, *entry;
     unsigned int elen;
+    long long value;
     sds s;
 
     zl = createIntList();
@@ -427,10 +442,15 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 0);
-        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
+        while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
-            fwrite(entry,elen,1,stdout);
-            printf(" (length %d)\n", elen);
+            if (entry) {
+                fwrite(entry,elen,1,stdout);
+            } else {
+                printf("%lld", value);
+            }
+            p = ziplistNext(p);
+            printf("\n");
         }
         printf("\n");
     }
@@ -439,10 +459,15 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 1);
-        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
+        while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
-            fwrite(entry,elen,1,stdout);
-            printf(" (length %d)\n", elen);
+            if (entry) {
+                fwrite(entry,elen,1,stdout);
+            } else {
+                printf("%lld", value);
+            }
+            p = ziplistNext(p);
+            printf("\n");
         }
         printf("\n");
     }
@@ -451,19 +476,24 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 2);
-        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
+        while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
-            fwrite(entry,elen,1,stdout);
-            printf(" (length %d)\n", elen);
+            if (entry) {
+                fwrite(entry,elen,1,stdout);
+            } else {
+                printf("%lld", value);
+            }
+            p = ziplistNext(p);
+            printf("\n");
         }
         printf("\n");
     }
 
     printf("Iterate starting out of range:\n");
     {
         zl = createList();
-        p = ziplistIndex(zl, 3);
-        if (ziplistNext(p, &entry, NULL, &elen) == NULL) {
+        p = ziplistIndex(zl, 4);
+        if (!ziplistGet(p, &entry, &elen, &value)) {
             printf("No entry\n");
         } else {
             printf("ERROR\n");
@@ -510,15 +540,19 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 0);
-        while ((p = ziplistNext(p, &q, &entry, &elen)) != NULL) {
-            if (strncmp("foo", entry, elen) == 0) {
+        while (ziplistGet(p, &entry, &elen, &value)) {
+            if (entry && strncmp("foo", entry, elen) == 0) {
                 printf("Delete foo\n");
-                zl = ziplistDelete(zl, &q);
-                p = q;
+                zl = ziplistDelete(zl, &p);
             } else {
                 printf("Entry: ");
-                fwrite(entry,elen,1,stdout);
-                printf(" (length %d)\n", elen);
+                if (entry) {
+                    fwrite(entry,elen,1,stdout);
+                } else {
+                    printf("%lld", value);
+                }
+                p = ziplistNext(p);
+                printf("\n");
             }
         }
         printf("\n");