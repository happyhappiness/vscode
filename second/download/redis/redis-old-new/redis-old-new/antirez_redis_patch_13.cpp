@@ -220,7 +220,8 @@ int redis_check_aof_main(int argc, char **argv) {
                 printf("Successfully truncated AOF\n");
             }
         } else {
-            printf("AOF is not valid\n");
+            printf("AOF is not valid. "
+                   "Use the --fix option to try fixing it.\n");
             exit(1);
         }
     } else {