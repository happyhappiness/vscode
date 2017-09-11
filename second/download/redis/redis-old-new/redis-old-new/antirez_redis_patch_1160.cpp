@@ -729,7 +729,15 @@ static int parseOptions(int argc, char **argv) {
             sdsfree(version);
             exit(0);
         } else {
-            break;
+            if (argv[i][0] == '-') {
+                fprintf(stderr,
+                    "Unrecognized option or bad number of args for: '%s'\n",
+                    argv[i]);
+                exit(1);
+            } else {
+                /* Likely the command name, stop here. */
+                break;
+            }
         }
     }
     return i;