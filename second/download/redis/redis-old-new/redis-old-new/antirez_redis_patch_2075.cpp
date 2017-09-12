@@ -130,8 +130,8 @@ unsigned char *ziplistNext(unsigned char *p, unsigned char **entry, unsigned int
     return p;
 }
 
-/* Delete one or more entries from the ziplist. */
-unsigned char *ziplistDelete(unsigned char *zl, unsigned int index, unsigned int num) {
+/* Delete a range of entries from the ziplist. */
+unsigned char *ziplistDeleteRange(unsigned char *zl, unsigned int index, unsigned int num) {
     unsigned char *p, *first = ziplistIndex(zl, index);
     unsigned int i, deleted = 0, totlen, newlen;
     for (p = first, i = 0; *p != ZIP_END && i < num; i++) {
@@ -245,35 +245,35 @@ int main(int argc, char **argv) {
     printf("Delete inclusive range 0,0:\n");
     {
         zl = createList();
-        zl = ziplistDelete(zl, 0, 1);
+        zl = ziplistDeleteRange(zl, 0, 1);
         ziplistRepr(zl);
     }
 
     printf("Delete inclusive range 0,1:\n");
     {
         zl = createList();
-        zl = ziplistDelete(zl, 0, 2);
+        zl = ziplistDeleteRange(zl, 0, 2);
         ziplistRepr(zl);
     }
 
     printf("Delete inclusive range 1,2:\n");
     {
         zl = createList();
-        zl = ziplistDelete(zl, 1, 2);
+        zl = ziplistDeleteRange(zl, 1, 2);
         ziplistRepr(zl);
     }
 
     printf("Delete with start index out of range:\n");
     {
         zl = createList();
-        zl = ziplistDelete(zl, 5, 1);
+        zl = ziplistDeleteRange(zl, 5, 1);
         ziplistRepr(zl);
     }
 
     printf("Delete with num overflow:\n");
     {
         zl = createList();
-        zl = ziplistDelete(zl, 1, 5);
+        zl = ziplistDeleteRange(zl, 1, 5);
         ziplistRepr(zl);
     }
 