@@ -551,7 +551,7 @@ void ziplistRepr(unsigned char *zl) {
         if (entry.encoding == ZIP_ENC_RAW) {
             fwrite(p,entry.len,1,stdout);
         } else {
-            printf("%lld", zipLoadInteger(p,entry.encoding));
+            printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
         }
         printf("\n");
         p += entry.len;