@@ -365,6 +365,28 @@ unsigned char *ziplistDelete(unsigned char *zl, unsigned char **p) {
     return zl;
 }
 
+/* Compare entry pointer to by 'p' with 'entry'. Return 1 if equal. */
+unsigned int ziplistCompare(unsigned char *p, unsigned char *entry, unsigned int elen) {
+    unsigned int zlen, lensize;
+    char encoding;
+    long long zval, eval;
+    if (*p == ZIP_END) return 0;
+
+    zlen = zipDecodeLength(p,&lensize);
+    if (zipTryEncoding(entry,&eval,&encoding)) {
+        /* Do integer compare */
+        zval = zipLoadInteger(p+lensize,ZIP_ENCODING(p));
+        return zval == eval;
+    } else {
+        /* Raw compare */
+        if (zlen == elen) {
+            return memcmp(p+lensize,entry,elen) == 0;
+        } else {
+            return 0;
+        }
+    }
+}
+
 void ziplistRepr(unsigned char *zl) {
     unsigned char *p, encoding;
     unsigned int l, lsize;
@@ -557,7 +579,31 @@ int main(int argc, char **argv) {
         }
         printf("\n");
         ziplistRepr(zl);
-        printf("\n");
+    }
+
+    printf("Compare strings with ziplist entries:\n");
+    {
+        zl = createList();
+        p = ziplistIndex(zl, 0);
+        if (!ziplistCompare(p,"hello",5)) {
+            printf("ERROR\n");
+            return;
+        }
+        if (ziplistCompare(p,"hella",5)) {
+            printf("ERROR\n");
+            return;
+        }
+
+        p = ziplistIndex(zl, 3);
+        if (!ziplistCompare(p,"1024",4)) {
+            printf("ERROR\n");
+            return;
+        }
+        if (ziplistCompare(p,"1025",4)) {
+            printf("ERROR\n");
+            return;
+        }
+        printf("SUCCESS\n");
     }
 
     return 0;