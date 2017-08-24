@@ -7,6 +7,7 @@
 
 int main ()
 {
+  int class = 0;
   if ( LibC1Func() != 2.0 )
     {
     printf("Problem with libc1\n");
@@ -17,6 +18,6 @@ int main ()
     printf("Problem with libc2\n");
     return 1;
     }
-  printf("Foo: %s\n", foo);
+  printf("Foo: %s %d\n", foo, class);
   return 0;
 }