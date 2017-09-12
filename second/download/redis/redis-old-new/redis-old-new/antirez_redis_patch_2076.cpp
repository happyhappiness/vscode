@@ -130,6 +130,27 @@ unsigned char *ziplistNext(unsigned char *p, unsigned char **entry, unsigned int
     return p;
 }
 
+/* Delete one or more entries from the ziplist. */
+unsigned char *ziplistDelete(unsigned char *zl, unsigned int index, unsigned int num) {
+    unsigned char *p, *first = ziplistIndex(zl, index);
+    unsigned int i, deleted = 0, totlen, newlen;
+    for (p = first, i = 0; *p != ZIP_END && i < num; i++) {
+        p += zipRawEntryLength(p);
+        deleted++;
+    }
+
+    totlen = p-first;
+    if (totlen > 0) {
+        /* Move current tail to the new tail when there *is* a tail */
+        if (*p != ZIP_END) memmove(first,p,ZIPLIST_BYTES(zl)-(p-zl)-1);
+
+        /* Resize and update length */
+        zl = ziplistResize(zl, ZIPLIST_BYTES(zl)-totlen);
+        if (ZIPLIST_LENGTH(zl) < ZIP_BIGLEN) ZIPLIST_LENGTH(zl) -= deleted;
+    }
+    return zl;
+}
+
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p;
     unsigned int l;
@@ -218,6 +239,42 @@ int main(int argc, char **argv) {
         } else {
             printf("ERROR\n");
         }
+        printf("\n");
+    }
+
+    printf("Delete inclusive range 0,0:\n");
+    {
+        zl = createList();
+        zl = ziplistDelete(zl, 0, 1);
+        ziplistRepr(zl);
+    }
+
+    printf("Delete inclusive range 0,1:\n");
+    {
+        zl = createList();
+        zl = ziplistDelete(zl, 0, 2);
+        ziplistRepr(zl);
+    }
+
+    printf("Delete inclusive range 1,2:\n");
+    {
+        zl = createList();
+        zl = ziplistDelete(zl, 1, 2);
+        ziplistRepr(zl);
+    }
+
+    printf("Delete with start index out of range:\n");
+    {
+        zl = createList();
+        zl = ziplistDelete(zl, 5, 1);
+        ziplistRepr(zl);
+    }
+
+    printf("Delete with num overflow:\n");
+    {
+        zl = createList();
+        zl = ziplistDelete(zl, 1, 5);
+        ziplistRepr(zl);
     }
 
     return 0;