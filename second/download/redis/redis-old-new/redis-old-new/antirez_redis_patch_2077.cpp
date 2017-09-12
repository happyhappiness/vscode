@@ -120,12 +120,11 @@ unsigned char *ziplistIndex(unsigned char *zl, unsigned int index) {
 
 /* Store entry at current position in sds *value and return pointer
  * to the next entry. */
-unsigned char *ziplistNext(unsigned char *p, sds *value) {
+unsigned char *ziplistNext(unsigned char *p, unsigned char **entry, unsigned int *elen) {
     if (*p == ZIP_END) return NULL;
-    if (value) {
-        unsigned int len;
-        len = zipDecodeLength(p);
-        *value = sdsnewlen(p+zipEncodeLength(NULL,len),len);
+    if (entry) {
+        *elen = zipDecodeLength(p);
+        *entry = p+ZIP_LEN_BYTES(*elen);
     }
     p += zipRawEntryLength(p);
     return p;
@@ -159,7 +158,8 @@ unsigned char *createList() {
 }
 
 int main(int argc, char **argv) {
-    unsigned char *zl, *p;
+    unsigned char *zl, *p, *entry;
+    unsigned int elen;
     sds s;
 
     zl = createList();
@@ -177,8 +177,10 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 0);
-        while ((p = ziplistNext(p, &s)) != NULL) {
-            printf("Entry: %s (length %ld)\n", s, sdslen(s));
+        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
+            printf("Entry: ");
+            fwrite(entry,elen,1,stdout);
+            printf(" (length %d)\n", elen);
         }
         printf("\n");
     }
@@ -187,8 +189,10 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 1);
-        while ((p = ziplistNext(p, &s)) != NULL) {
-            printf("Entry: %s (length %ld)\n", s, sdslen(s));
+        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
+            printf("Entry: ");
+            fwrite(entry,elen,1,stdout);
+            printf(" (length %d)\n", elen);
         }
         printf("\n");
     }
@@ -197,8 +201,10 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 2);
-        while ((p = ziplistNext(p, &s)) != NULL) {
-            printf("Entry: %s (length %ld)\n", s, sdslen(s));
+        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
+            printf("Entry: ");
+            fwrite(entry,elen,1,stdout);
+            printf(" (length %d)\n", elen);
         }
         printf("\n");
     }
@@ -207,7 +213,7 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 3);
-        if (ziplistNext(p, &s) == NULL) {
+        if (ziplistNext(p, &entry, &elen) == NULL) {
             printf("No entry\n");
         } else {
             printf("ERROR\n");