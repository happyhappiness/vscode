@@ -402,15 +402,29 @@ unsigned char *ziplistPop(unsigned char *zl, sds *target, int where) {
     return zl;
 }
 
-/* Returns an offset to use for iterating with ziplistNext. */
-unsigned char *ziplistIndex(unsigned char *zl, unsigned int index) {
-    unsigned char *p = zl+ZIPLIST_HEADER_SIZE;
-    unsigned int i = 0;
-    for (; i < index; i++) {
-        if (*p == ZIP_END) break;
-        p += zipRawEntryLength(p);
+/* Returns an offset to use for iterating with ziplistNext. When the given
+ * index is negative, the list is traversed back to front. When the list
+ * doesn't contain an element at the provided index, NULL is returned. */
+unsigned char *ziplistIndex(unsigned char *zl, int index) {
+    unsigned char *p;
+    zlentry entry;
+    if (index < 0) {
+        index = (-index)-1;
+        p = ZIPLIST_ENTRY_TAIL(zl);
+        if (p[0] != ZIP_END) {
+            entry = zipEntry(p);
+            while (entry.prevrawlen > 0 && index--) {
+                p -= entry.prevrawlen;
+                entry = zipEntry(p);
+            }
+        }
+    } else {
+        p = ZIPLIST_ENTRY_HEAD(zl);
+        while (p[0] != ZIP_END && index--) {
+            p += zipRawEntryLength(p);
+        }
     }
-    return p;
+    return p[0] == ZIP_END || index > 0 ? NULL : p;
 }
 
 /* Return pointer to next entry in ziplist. */
@@ -424,7 +438,7 @@ unsigned char *ziplistNext(unsigned char *p) {
  * Return 0 if 'p' points to the end of the zipmap, 1 otherwise. */
 unsigned int ziplistGet(unsigned char *p, char **sstr, unsigned int *slen, long long *sval) {
     zlentry entry;
-    if (*p == ZIP_END) return 0;
+    if (p == NULL || p[0] == ZIP_END) return 0;
     if (sstr) *sstr = NULL;
 
     entry = zipEntry(p);
@@ -444,7 +458,7 @@ unsigned int ziplistGet(unsigned char *p, char **sstr, unsigned int *slen, long
 /* Delete a range of entries from the ziplist. */
 unsigned char *ziplistDeleteRange(unsigned char *zl, unsigned int index, unsigned int num) {
     unsigned char *p = ziplistIndex(zl,index);
-    return __ziplistDelete(zl,p,num);
+    return p == NULL ? zl : __ziplistDelete(zl,p,num);
 }
 
 /* Delete a single entry from the ziplist, pointed to by *p.
@@ -590,6 +604,83 @@ int main(int argc, char **argv) {
     printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
     ziplistRepr(zl);
 
+    printf("Get element at index 3:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 3);
+        if (!ziplistGet(p, &entry, &elen, &value)) {
+            printf("ERROR: Could not access index 3\n");
+            return 1;
+        }
+        if (entry) {
+            fwrite(entry,elen,1,stdout);
+            printf("\n");
+        } else {
+            printf("%lld\n", value);
+        }
+        printf("\n");
+    }
+
+    printf("Get element at index 4 (out of range):\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 4);
+        if (p == NULL) {
+            printf("No entry\n");
+        } else {
+            printf("ERROR: Out of range index should return NULL, returned offset: %ld\n", p-zl);
+            return 1;
+        }
+        printf("\n");
+    }
+
+    printf("Get element at index -1 (last element):\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, -1);
+        if (!ziplistGet(p, &entry, &elen, &value)) {
+            printf("ERROR: Could not access index -1\n");
+            return 1;
+        }
+        if (entry) {
+            fwrite(entry,elen,1,stdout);
+            printf("\n");
+        } else {
+            printf("%lld\n", value);
+        }
+        printf("\n");
+    }
+
+    printf("Get element at index -4 (first element):\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, -4);
+        if (!ziplistGet(p, &entry, &elen, &value)) {
+            printf("ERROR: Could not access index -4\n");
+            return 1;
+        }
+        if (entry) {
+            fwrite(entry,elen,1,stdout);
+            printf("\n");
+        } else {
+            printf("%lld\n", value);
+        }
+        printf("\n");
+    }
+
+    printf("Get element at index -5 (reverse out of range):\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, -5);
+        if (p == NULL) {
+            printf("No entry\n");
+        } else {
+            printf("ERROR: Out of range index should return NULL, returned offset: %ld\n", p-zl);
+            return 1;
+        }
+        printf("\n");
+    }
+
     printf("Iterate list from 0 to end:\n");
     {
         zl = createList();