@@ -43,7 +43,7 @@
  * The string is always null-termined (all the sds strings are, always) so
  * even if you create an sds string with:
  *
- * mystring = sdsnewlen("abc",3");
+ * mystring = sdsnewlen("abc",3);
  *
  * You can print the string with printf() as there is an implicit \0 at the
  * end of the string. However the string is binary safe and can contain
@@ -109,7 +109,7 @@ void sdsupdatelen(sds s) {
     sh->len = reallen;
 }
 
-/* Modify an sds string on-place to make it empty (zero length).
+/* Modify an sds string in-place to make it empty (zero length).
  * However all the existing buffer is not discarded but set as free space
  * so that next append operations will not require allocations up to the
  * number of bytes previously available. */