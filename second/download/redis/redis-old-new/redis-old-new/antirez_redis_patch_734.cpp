@@ -1511,7 +1511,7 @@ static void findBigKeys(void) {
     for(i=0;i<TYPE_NONE; i++) {
         maxkeys[i] = sdsempty();
         if(!maxkeys[i]) {
-            fprintf(stderr, "Failed to allocate memory for largest key names!");
+            fprintf(stderr, "Failed to allocate memory for largest key names!\n");
             exit(1);
         }
     }