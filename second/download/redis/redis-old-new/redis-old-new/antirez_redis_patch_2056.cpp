@@ -428,14 +428,27 @@ unsigned char *ziplistIndex(unsigned char *zl, int index) {
 }
 
 /* Return pointer to next entry in ziplist. */
-unsigned char *ziplistNext(unsigned char *p) {
+unsigned char *ziplistNext(unsigned char *zl, unsigned char *p) {
+    ((void) zl);
     return (p[0] == ZIP_END) ? NULL : p+zipRawEntryLength(p);
 }
 
 /* Return pointer to previous entry in ziplist. */
-unsigned char *ziplistPrev(unsigned char *p) {
-    zlentry entry = zipEntry(p);
-    return (entry.prevrawlen == 0) ? NULL : p-entry.prevrawlen;
+unsigned char *ziplistPrev(unsigned char *zl, unsigned char *p) {
+    zlentry entry;
+
+    /* Iterating backwards from ZIP_END should return the tail. When "p" is
+     * equal to the first element of the list, we're already at the head,
+     * and should return NULL. */
+    if (p[0] == ZIP_END) {
+        p = ZIPLIST_ENTRY_TAIL(zl);
+        return (p[0] == ZIP_END) ? NULL : p;
+    } else if (p == ZIPLIST_ENTRY_HEAD(zl)) {
+        return NULL;
+    } else {
+        entry = zipEntry(p);
+        return p-entry.prevrawlen;
+    }
 }
 
 /* Get entry pointer to by 'p' and store in either 'e' or 'v' depending
@@ -709,7 +722,7 @@ int main(int argc, char **argv) {
             } else {
                 printf("%lld", value);
             }
-            p = ziplistNext(p);
+            p = ziplistNext(zl,p);
             printf("\n");
         }
         printf("\n");
@@ -726,7 +739,7 @@ int main(int argc, char **argv) {
             } else {
                 printf("%lld", value);
             }
-            p = ziplistNext(p);
+            p = ziplistNext(zl,p);
             printf("\n");
         }
         printf("\n");
@@ -743,7 +756,7 @@ int main(int argc, char **argv) {
             } else {
                 printf("%lld", value);
             }
-            p = ziplistNext(p);
+            p = ziplistNext(zl,p);
             printf("\n");
         }
         printf("\n");
@@ -772,7 +785,7 @@ int main(int argc, char **argv) {
             } else {
                 printf("%lld", value);
             }
-            p = ziplistPrev(p);
+            p = ziplistPrev(zl,p);
             printf("\n");
         }
         printf("\n");
@@ -789,7 +802,8 @@ int main(int argc, char **argv) {
             } else {
                 printf("%lld", value);
             }
-            zl = ziplistDelete(zl, &p, ZIPLIST_HEAD);
+            zl = ziplistDelete(zl,&p);
+            p = ziplistPrev(zl,p);
             printf("\n");
         }
         printf("\n");