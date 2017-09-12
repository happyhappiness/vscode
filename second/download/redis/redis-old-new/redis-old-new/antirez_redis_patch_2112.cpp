@@ -154,16 +154,26 @@ int main(int argc, char **argv) {
     }
 
     long pos = process(fp);
-    if (pos < size) {
+    long diff = size-pos;
+    if (diff > 0) {
         if (fix) {
+            char buf[2];
+            printf("This will shrink the AOF from %ld bytes, with %ld bytes, to %ld bytes\n",size,diff,pos);
+            printf("Continue? [y/N]: ");
+            if (fgets(buf,sizeof(buf),stdin) == NULL ||
+                strncasecmp(buf,"y",1) != 0) {
+                    printf("Aborting...\n");
+                    exit(1);
+            }
             if (ftruncate(fileno(fp), pos) == -1) {
-                printf("Could not truncate AOF to size %ld\n", pos);
+                printf("Failed to truncate AOF\n");
                 exit(1);
             } else {
-                printf("AOF succesfully truncated to %ld bytes\n", pos);
+                printf("Successfully truncated AOF\n");
             }
         } else {
-            printf("First invalid operation at offset %ld\n", pos);
+            printf("AOF is not valid\n");
+            exit(1);
         }
     } else {
         printf("AOF is valid\n");