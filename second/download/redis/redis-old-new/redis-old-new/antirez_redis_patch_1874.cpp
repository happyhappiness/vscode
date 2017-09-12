@@ -374,14 +374,14 @@ void zipmapRepr(unsigned char *p) {
             l = zipmapDecodeLength(p);
             printf("{key %u}",l);
             p += zipmapEncodeLength(NULL,l);
-            fwrite(p,l,1,stdout);
+            if (l != 0 && fwrite(p,l,1,stdout) == 0) perror("fwrite");
             p += l;
 
             l = zipmapDecodeLength(p);
             printf("{value %u}",l);
             p += zipmapEncodeLength(NULL,l);
             e = *p++;
-            fwrite(p,l,1,stdout);
+            if (l != 0 && fwrite(p,l,1,stdout) == 0) perror("fwrite");
             p += l+e;
             if (e) {
                 printf("[");