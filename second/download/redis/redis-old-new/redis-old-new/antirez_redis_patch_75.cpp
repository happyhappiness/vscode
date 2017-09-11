@@ -1029,7 +1029,7 @@ void ziplistRepr(unsigned char *zl) {
 
     printf(
         "{total bytes %d} "
-        "{length %u}\n"
+        "{num entries %u}\n"
         "{tail offset %u}\n",
         intrev32ifbe(ZIPLIST_BYTES(zl)),
         intrev16ifbe(ZIPLIST_LENGTH(zl)),
@@ -1038,16 +1038,15 @@ void ziplistRepr(unsigned char *zl) {
     while(*p != ZIP_END) {
         zipEntry(p, &entry);
         printf(
-            "{"
-                "addr 0x%08lx, "
-                "index %2d, "
-                "offset %5ld, "
-                "rl: %5u, "
-                "hs %2u, "
-                "pl: %5u, "
-                "pls: %2u, "
-                "payload %5u"
-            "} ",
+            "{\n"
+                "\taddr 0x%08lx,\n"
+                "\tindex %2d,\n"
+                "\toffset %5ld,\n"
+                "\thdr+entry len: %5u,\n"
+                "\thdr len%2u,\n"
+                "\tprevrawlen: %5u,\n"
+                "\tprevrawlensize: %2u,\n"
+                "\tpayload %5u\n",
             (long unsigned)p,
             index,
             (unsigned long) (p-zl),
@@ -1056,8 +1055,14 @@ void ziplistRepr(unsigned char *zl) {
             entry.prevrawlen,
             entry.prevrawlensize,
             entry.len);
+        printf("\tbytes: ");
+        for (unsigned int i = 0; i < entry.headersize+entry.len; i++) {
+            printf("%02x|",p[i]);
+        }
+        printf("\n");
         p += entry.headersize;
         if (ZIP_IS_STR(entry.encoding)) {
+            printf("\t[str]");
             if (entry.len > 40) {
                 if (fwrite(p,40,1,stdout) == 0) perror("fwrite");
                 printf("...");
@@ -1066,9 +1071,9 @@ void ziplistRepr(unsigned char *zl) {
                     fwrite(p,entry.len,1,stdout) == 0) perror("fwrite");
             }
         } else {
-            printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
+            printf("\t[int]%lld", (long long) zipLoadInteger(p,entry.encoding));
         }
-        printf("\n");
+        printf("\n}\n");
         p += entry.len;
         index++;
     }