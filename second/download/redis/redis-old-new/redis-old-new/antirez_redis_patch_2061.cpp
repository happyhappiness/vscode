@@ -469,13 +469,19 @@ unsigned char *ziplistInsert(unsigned char *zl, unsigned char *p, char *s, unsig
 /* Delete a single entry from the ziplist, pointed to by *p.
  * Also update *p in place, to be able to iterate over the
  * ziplist, while deleting entries. */
-unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
+unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p, int direction) {
     unsigned int offset = *p-zl;
     zl = __ziplistDelete(zl,*p,1);
 
     /* Store pointer to current element in p, because ziplistDelete will
-     * do a realloc which might result in a different "zl"-pointer. */
-    *p = zl+offset;
+     * do a realloc which might result in a different "zl"-pointer.
+     * When the delete direction is back to front, we might delete the last
+     * entry and end up with "p" pointing to ZIP_END, so check this. */
+    if (*(zl+offset) == ZIP_END && direction == ZIPLIST_HEAD) {
+        *p = ZIPLIST_ENTRY_TAIL(zl);
+    } else {
+        *p = zl+offset;
+    }
     return zl;
 }
 
@@ -755,6 +761,40 @@ int main(int argc, char **argv) {
         printf("\n");
     }
 
+    printf("Iterate from back to front:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, -1);
+        while (ziplistGet(p, &entry, &elen, &value)) {
+            printf("Entry: ");
+            if (entry) {
+                fwrite(entry,elen,1,stdout);
+            } else {
+                printf("%lld", value);
+            }
+            p = ziplistPrev(p);
+            printf("\n");
+        }
+        printf("\n");
+    }
+
+    printf("Iterate from back to front, deleting all items:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, -1);
+        while (ziplistGet(p, &entry, &elen, &value)) {
+            printf("Entry: ");
+            if (entry) {
+                fwrite(entry,elen,1,stdout);
+            } else {
+                printf("%lld", value);
+            }
+            zl = ziplistDelete(zl, &p, ZIPLIST_HEAD);
+            printf("\n");
+        }
+        printf("\n");
+    }
+
     printf("Delete inclusive range 0,0:\n");
     {
         zl = createList();
@@ -797,7 +837,7 @@ int main(int argc, char **argv) {
         while (ziplistGet(p, &entry, &elen, &value)) {
             if (entry && strncmp("foo", entry, elen) == 0) {
                 printf("Delete foo\n");
-                zl = ziplistDelete(zl, &p);
+                zl = ziplistDelete(zl, &p, ZIPLIST_TAIL);
             } else {
                 printf("Entry: ");
                 if (entry) {