                 printf("Failed to truncate AOF\n");
                 exit(1);
             } else {
                 printf("Successfully truncated AOF\n");
             }
         } else {
-            printf("AOF is not valid\n");
+            printf("AOF is not valid. "
+                   "Use the --fix option to try fixing it.\n");
             exit(1);
         }
     } else {
         printf("AOF is valid\n");
     }
 
     fclose(fp);
-    return 0;
+    exit(0);
 }
