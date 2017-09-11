@@ -614,7 +614,7 @@ void process(void) {
             printf("RDB version >= 5 but no room for checksum.\n");
             exit(1);
         }
-        positions[0].size -= 8;;
+        positions[0].size -= 8;
     }
 
     level = 1;