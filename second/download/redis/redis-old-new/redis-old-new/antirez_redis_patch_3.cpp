@@ -194,7 +194,7 @@ int redis_check_aof_main(int argc, char **argv) {
                 printf("RDB preamble of AOF file is not sane, aborting.\n");
                 exit(1);
             } else {
-                printf("RDB preamble is OK, proceding with AOF tail...\n");
+                printf("RDB preamble is OK, proceeding with AOF tail...\n");
             }
         }
     }