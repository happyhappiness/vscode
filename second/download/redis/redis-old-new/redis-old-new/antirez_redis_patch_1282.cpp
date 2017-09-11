@@ -500,12 +500,13 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
     totlen = p-first.p;
     if (totlen > 0) {
         if (p[0] != ZIP_END) {
-            /* Tricky: storing the prevlen in this entry might reduce or
-             * increase the number of bytes needed, compared to the current
-             * prevlen. Note that we can always store this length because
-             * it was previously stored by an entry that is being deleted. */
+            /* Storing `prevrawlen` in this entry may increase or decrease the
+             * number of bytes required compare to the current `prevrawlen`.
+             * There always is room to store this, because it was previously
+             * stored by an entry that is now being deleted. */
             nextdiff = zipPrevLenByteDiff(p,first.prevrawlen);
-            zipPrevEncodeLength(p-nextdiff,first.prevrawlen);
+            p -= nextdiff;
+            zipPrevEncodeLength(p,first.prevrawlen);
 
             /* Update offset for tail */
             ZIPLIST_TAIL_OFFSET(zl) =
@@ -521,8 +522,8 @@ static unsigned char *__ziplistDelete(unsigned char *zl, unsigned char *p, unsig
             }
 
             /* Move tail to the front of the ziplist */
-            memmove(first.p,p-nextdiff,
-                intrev32ifbe(ZIPLIST_BYTES(zl))-(p-zl)-1+nextdiff);
+            memmove(first.p,p,
+                intrev32ifbe(ZIPLIST_BYTES(zl))-(p-zl)-1);
         } else {
             /* The entire tail was deleted. No need to move memory. */
             ZIPLIST_TAIL_OFFSET(zl) =
@@ -1034,6 +1035,22 @@ int randstring(char *target, unsigned int min, unsigned int max) {
     return len;
 }
 
+void verify(unsigned char *zl, zlentry *e) {
+    int i;
+    int len = ziplistLen(zl);
+    zlentry _e;
+
+    for (i = 0; i < len; i++) {
+        memset(&e[i], 0, sizeof(zlentry));
+        e[i] = zipEntry(ziplistIndex(zl, i));
+
+        memset(&_e, 0, sizeof(zlentry));
+        _e = zipEntry(ziplistIndex(zl, -len+i));
+
+        assert(memcmp(&e[i], &_e, sizeof(zlentry)) == 0);
+    }
+}
+
 int main(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
@@ -1315,6 +1332,43 @@ int main(int argc, char **argv) {
         printf("SUCCESS\n\n");
     }
 
+    printf("Regression test deleting next to last entries:\n");
+    {
+        char v[3][257];
+        zlentry e[3];
+        int i;
+
+        for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++) {
+            memset(v[i], 'a' + i, sizeof(v[0]));
+        }
+
+        v[0][256] = '\0';
+        v[1][  1] = '\0';
+        v[2][256] = '\0';
+
+        zl = ziplistNew();
+        for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++) {
+            zl = ziplistPush(zl, (unsigned char *) v[i], strlen(v[i]), ZIPLIST_TAIL);
+        }
+
+        verify(zl, e);
+
+        assert(e[0].prevrawlensize == 1);
+        assert(e[1].prevrawlensize == 5);
+        assert(e[2].prevrawlensize == 1);
+
+        /* Deleting entry 1 will increase `prevrawlensize` for entry 2 */
+        unsigned char *p = e[1].p;
+        zl = ziplistDelete(zl, &p);
+
+        verify(zl, e);
+
+        assert(e[0].prevrawlensize == 1);
+        assert(e[1].prevrawlensize == 5);
+
+        printf("SUCCESS\n\n");
+    }
+
     printf("Create long list and check indices:\n");
     {
         zl = ziplistNew();