@@ -120,12 +120,13 @@ unsigned char *ziplistIndex(unsigned char *zl, unsigned int index) {
 
 /* Store entry at current position in sds *value and return pointer
  * to the next entry. */
-unsigned char *ziplistNext(unsigned char *p, unsigned char **entry, unsigned int *elen) {
+unsigned char *ziplistNext(unsigned char *p, unsigned char **q, unsigned char **entry, unsigned int *elen) {
     if (*p == ZIP_END) return NULL;
     if (entry) {
         *elen = zipDecodeLength(p);
         *entry = p+ZIP_LEN_BYTES(*elen);
     }
+    if (q != NULL) *q = p;
     p += zipRawEntryLength(p);
     return p;
 }
@@ -198,7 +199,7 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 0);
-        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
+        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
             printf("Entry: ");
             fwrite(entry,elen,1,stdout);
             printf(" (length %d)\n", elen);
@@ -210,7 +211,7 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 1);
-        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
+        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
             printf("Entry: ");
             fwrite(entry,elen,1,stdout);
             printf(" (length %d)\n", elen);
@@ -222,7 +223,7 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 2);
-        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
+        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
             printf("Entry: ");
             fwrite(entry,elen,1,stdout);
             printf(" (length %d)\n", elen);
@@ -234,7 +235,7 @@ int main(int argc, char **argv) {
     {
         zl = createList();
         p = ziplistIndex(zl, 3);
-        if (ziplistNext(p, &entry, &elen) == NULL) {
+        if (ziplistNext(p, &entry, NULL, &elen) == NULL) {
             printf("No entry\n");
         } else {
             printf("ERROR\n");