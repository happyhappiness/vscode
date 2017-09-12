@@ -754,9 +754,9 @@ void ziplistRepr(unsigned char *zl) {
                 "pls: %2u, "
                 "payload %5u"
             "} ",
-            (long unsigned int)p,
+            (long unsigned)p,
             index,
-            p-zl,
+            (unsigned long) (p-zl),
             entry.headersize+entry.len,
             entry.headersize,
             entry.prevrawlen,
@@ -765,10 +765,11 @@ void ziplistRepr(unsigned char *zl) {
         p += entry.headersize;
         if (ZIP_IS_STR(entry.encoding)) {
             if (entry.len > 40) {
-                fwrite(p,40,1,stdout);
+                if (fwrite(p,40,1,stdout) == 0) perror("fwrite");
                 printf("...");
             } else {
-                fwrite(p,entry.len,1,stdout);
+                if (entry.len &&
+                    fwrite(p,entry.len,1,stdout) == 0) perror("fwrite");
             }
         } else {
             printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
@@ -857,7 +858,7 @@ void pop(unsigned char *zl, int where) {
             printf("Pop tail: ");
 
         if (vstr)
-            fwrite(vstr,vlen,1,stdout);
+            if (vlen && fwrite(vstr,vlen,1,stdout) == 0) perror("fwrite");
         else
             printf("%lld", vlong);
 
@@ -932,7 +933,7 @@ int main(int argc, char **argv) {
             return 1;
         }
         if (entry) {
-            fwrite(entry,elen,1,stdout);
+            if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             printf("\n");
         } else {
             printf("%lld\n", value);
@@ -962,7 +963,7 @@ int main(int argc, char **argv) {
             return 1;
         }
         if (entry) {
-            fwrite(entry,elen,1,stdout);
+            if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             printf("\n");
         } else {
             printf("%lld\n", value);
@@ -979,7 +980,7 @@ int main(int argc, char **argv) {
             return 1;
         }
         if (entry) {
-            fwrite(entry,elen,1,stdout);
+            if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             printf("\n");
         } else {
             printf("%lld\n", value);
@@ -1007,7 +1008,7 @@ int main(int argc, char **argv) {
         while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
             if (entry) {
-                fwrite(entry,elen,1,stdout);
+                if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             } else {
                 printf("%lld", value);
             }
@@ -1024,7 +1025,7 @@ int main(int argc, char **argv) {
         while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
             if (entry) {
-                fwrite(entry,elen,1,stdout);
+                if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             } else {
                 printf("%lld", value);
             }
@@ -1041,7 +1042,7 @@ int main(int argc, char **argv) {
         while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
             if (entry) {
-                fwrite(entry,elen,1,stdout);
+                if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             } else {
                 printf("%lld", value);
             }
@@ -1070,7 +1071,7 @@ int main(int argc, char **argv) {
         while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
             if (entry) {
-                fwrite(entry,elen,1,stdout);
+                if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             } else {
                 printf("%lld", value);
             }
@@ -1087,7 +1088,7 @@ int main(int argc, char **argv) {
         while (ziplistGet(p, &entry, &elen, &value)) {
             printf("Entry: ");
             if (entry) {
-                fwrite(entry,elen,1,stdout);
+                if (elen && fwrite(entry,elen,1,stdout) == 0) perror("fwrite");
             } else {
                 printf("%lld", value);
             }
@@ -1144,7 +1145,8 @@ int main(int argc, char **argv) {
             } else {
                 printf("Entry: ");
                 if (entry) {
-                    fwrite(entry,elen,1,stdout);
+                    if (elen && fwrite(entry,elen,1,stdout) == 0)
+                        perror("fwrite");
                 } else {
                     printf("%lld",value);
                 }