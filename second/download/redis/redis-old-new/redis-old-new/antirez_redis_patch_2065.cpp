@@ -496,24 +496,22 @@ unsigned int ziplistSize(unsigned char *zl) {
 }
 
 void ziplistRepr(unsigned char *zl) {
-    unsigned char *p, encoding;
-    unsigned int prevrawlensize, prevrawlen, lensize, len;
+    unsigned char *p;
+    zlentry entry;
 
     printf("{total bytes %d} {length %u}\n",ZIPLIST_BYTES(zl), ZIPLIST_LENGTH(zl));
     p = ziplistHead(zl);
     while(*p != ZIP_END) {
-        prevrawlen = zipDecodeLength(p,&prevrawlensize);
-        len = zipDecodeLength(p+prevrawlensize,&lensize);
-        printf("{offset %ld, header %u, payload %u} ",p-zl,prevrawlensize+lensize,len);
-        encoding = ZIP_ENCODING(p+prevrawlensize);
-        p += prevrawlensize+lensize;
-        if (encoding == ZIP_ENC_RAW) {
-            fwrite(p,len,1,stdout);
+        entry = zipEntry(p);
+        printf("{offset %ld, header %u, payload %u} ",p-zl,entry.headersize,entry.len);
+        p += entry.headersize;
+        if (entry.encoding == ZIP_ENC_RAW) {
+            fwrite(p,entry.len,1,stdout);
         } else {
-            printf("%lld", zipLoadInteger(p,encoding));
+            printf("%lld", zipLoadInteger(p,entry.encoding));
         }
         printf("\n");
-        p += len;
+        p += entry.len;
     }
     printf("{end}\n\n");
 }