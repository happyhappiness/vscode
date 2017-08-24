@@ -27,7 +27,7 @@
 int
 th_read_internal(TAR *t)
 {
-  int i;
+  ssize_t i;
   int num_zero_blocks = 0;
 
 #ifdef DEBUG
@@ -82,15 +82,15 @@ th_read_internal(TAR *t)
 #ifdef DEBUG
   printf("<== th_read_internal(): returning %d\n", i);
 #endif
-  return i;
+  return (int)i;
 }
 
 
 /* wrapper function for th_read_internal() to handle GNU extensions */
 int
 th_read(TAR *t)
 {
-  int i, j;
+  ssize_t i, j;
   size_t sz;
   char *ptr;
 
@@ -247,7 +247,7 @@ th_read(TAR *t)
 int
 th_write(TAR *t)
 {
-  int i, j;
+  ssize_t i, j;
   char type2;
   size_t sz, sz2;
   char *ptr;