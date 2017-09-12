@@ -124,7 +124,7 @@ static int zipTryEncoding(unsigned char *entry, long long *v, char *encoding) {
     char *eptr;
 
     if (entry[0] == '-' || (entry[0] >= '0' && entry[0] <= '9')) {
-        value = strtoll(entry,&eptr,10);
+        value = strtoll((char*)entry,&eptr,10);
         if (eptr[0] != '\0') return 0;
         if (value >= SHRT_MIN && value <= SHRT_MAX) {
             *encoding = ZIP_ENC_SHORT;
@@ -327,7 +327,7 @@ unsigned int ziplistGet(unsigned char *p, unsigned char **e, unsigned int *elen,
 /* Delete a range of entries from the ziplist. */
 unsigned char *ziplistDeleteRange(unsigned char *zl, unsigned int index, unsigned int num) {
     unsigned char *p, *first = ziplistIndex(zl, index);
-    unsigned int i, deleted = 0, totlen, newlen;
+    unsigned int i, totlen, deleted = 0;
     for (p = first, i = 0; *p != ZIP_END && i < num; i++) {
         p += zipRawEntryLength(p);
         deleted++;
@@ -419,7 +419,6 @@ unsigned int ziplistSize(unsigned char *zl) {
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p, encoding;
     unsigned int l, lsize;
-    long long value;
 
     printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
     p = ziplistHead(zl);