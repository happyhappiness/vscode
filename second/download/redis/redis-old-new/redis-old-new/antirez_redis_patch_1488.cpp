@@ -298,7 +298,7 @@ unsigned char *zipmapDel(unsigned char *zm, unsigned char *key, unsigned int kle
     return zm;
 }
 
-/* Call it before to iterate trought elements via zipmapNext() */
+/* Call before iterating through elements via zipmapNext() */
 unsigned char *zipmapRewind(unsigned char *zm) {
     return zm+1;
 }
@@ -452,7 +452,7 @@ int main(void) {
                 vlen, vlen, value);
         }
     }
-    printf("\nIterate trought elements:\n");
+    printf("\nIterate through elements:\n");
     {
         unsigned char *i = zipmapRewind(zm);
         unsigned char *key, *value;