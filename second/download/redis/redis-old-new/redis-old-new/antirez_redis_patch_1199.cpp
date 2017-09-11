@@ -704,7 +704,8 @@ int memtest_test_linux_anonymous_maps(void) {
 
         start_vect[regions] = start_addr;
         size_vect[regions] = size;
-        printf("Testing %lx %lu\n", start_vect[regions], size_vect[regions]);
+        printf("Testing %lx %lu\n", (unsigned long) start_vect[regions],
+                                    (unsigned long) size_vect[regions]);
         regions++;
     }
 