     for (i = 0; i < errors.level; i++) {
         printf("0x%08lx - %s\n",
             (unsigned long) errors.offset[i], errors.error[i]);
     }
 }
 
-void process() {
+void process(void) {
     uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
     entry entry;
     int dump_version = processHeader();
 
     /* Exclude the final checksum for RDB >= 5. Will be checked at the end. */
     if (dump_version >= 5) {
         if (positions[0].size < 8) {
             printf("RDB version >= 5 but no room for checksum.\n");
             exit(1);
         }
-        positions[0].size -= 8;;
+        positions[0].size -= 8;
     }
 
     level = 1;
     while(positions[0].offset < positions[0].size) {
         positions[1] = positions[0];
 
