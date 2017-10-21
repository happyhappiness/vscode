     fprintf(header, "local const ct_data static_dtree[D_CODES] = {\n");
     for (i = 0; i < D_CODES; i++) {
         fprintf(header, "{{%2u},{%2u}}%s", static_dtree[i].Code,
                 static_dtree[i].Len, SEPARATOR(i, D_CODES-1, 5));
     }
 
-    fprintf(header, "const uch _dist_code[DIST_CODE_LEN] = {\n");
+    fprintf(header, "const uch ZLIB_INTERNAL _dist_code[DIST_CODE_LEN] = {\n");
     for (i = 0; i < DIST_CODE_LEN; i++) {
         fprintf(header, "%2u%s", _dist_code[i],
                 SEPARATOR(i, DIST_CODE_LEN-1, 20));
     }
 
-    fprintf(header, "const uch _length_code[MAX_MATCH-MIN_MATCH+1]= {\n");
+    fprintf(header,
+        "const uch ZLIB_INTERNAL _length_code[MAX_MATCH-MIN_MATCH+1]= {\n");
     for (i = 0; i < MAX_MATCH-MIN_MATCH+1; i++) {
         fprintf(header, "%2u%s", _length_code[i],
                 SEPARATOR(i, MAX_MATCH-MIN_MATCH, 20));
     }
 
     fprintf(header, "local const int base_length[LENGTH_CODES] = {\n");
