@@ -152,6 +152,27 @@ unsigned char *ziplistDeleteRange(unsigned char *zl, unsigned int index, unsigne
     return zl;
 }
 
+/* Delete a single entry from the ziplist, pointed to by *p.
+ * Also update *p in place, to be able to iterate over the
+ * ziplist, while deleting entries. */
+unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
+    unsigned int offset = *p-zl, tail, len;
+    len = zipRawEntryLength(*p);
+    tail = ZIPLIST_BYTES(zl)-offset-len-1;
+
+    /* Move current tail to the new tail when there *is* a tail */
+    if (tail > 0) memmove(*p,*p+len,tail);
+
+    /* Resize and update length */
+    zl = ziplistResize(zl, ZIPLIST_BYTES(zl)-len);
+    if (ZIPLIST_LENGTH(zl) < ZIP_BIGLEN) ZIPLIST_LENGTH(zl)--;
+
+    /* Store new pointer to current element in p.
+     * This needs to be done because zl can change on realloc. */
+    *p = zl+offset;
+    return zl;
+}
+
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p;
     unsigned int l;
@@ -180,7 +201,7 @@ unsigned char *createList() {
 }
 
 int main(int argc, char **argv) {
-    unsigned char *zl, *p, *entry;
+    unsigned char *zl, *p, *q, *entry;
     unsigned int elen;
     sds s;
 
@@ -278,6 +299,26 @@ int main(int argc, char **argv) {
         ziplistRepr(zl);
     }
 
+    printf("Delete foo while iterating:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 0);
+        while ((p = ziplistNext(p, &q, &entry, &elen)) != NULL) {
+            if (strncmp("foo", entry, elen) == 0) {
+                printf("Delete foo\n");
+                zl = ziplistDelete(zl, &q);
+                p = q;
+            } else {
+                printf("Entry: ");
+                fwrite(entry,elen,1,stdout);
+                printf(" (length %d)\n", elen);
+            }
+        }
+        printf("\n");
+        ziplistRepr(zl);
+        printf("\n");
+    }
+
     return 0;
 }
 #endif