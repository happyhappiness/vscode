@@ -917,6 +917,13 @@ static int parseOptions(int argc, char **argv) {
             }
         }
     }
+
+    /* --ldb requires --eval. */
+    if (config.eval_ldb && config.eval == NULL) {
+        fprintf(stderr,"Options --ldb and --ldb-sync-mode require --eval.\n");
+        fprintf(stderr,"Try %s --help for more information.\n", argv[0]);
+        exit(1);
+    }
     return i;
 }
 