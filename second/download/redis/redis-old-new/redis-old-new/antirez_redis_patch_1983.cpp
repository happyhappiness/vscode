@@ -496,13 +496,15 @@ void printCentered(int indent, int width, char* body) {
 
 void printValid(uint64_t ops, uint64_t bytes) {
     char body[80];
-    sprintf(body, "Processed %llu valid opcodes (in %llu bytes)", ops, bytes);
+    sprintf(body, "Processed %llu valid opcodes (in %llu bytes)",
+        (unsigned long long) ops, (unsigned long long) bytes);
     printCentered(4, 80, body);
 }
 
 void printSkipped(uint64_t bytes, uint64_t offset) {
     char body[80];
-    sprintf(body, "Skipped %llu bytes (resuming at 0x%08llx)", bytes, offset);
+    sprintf(body, "Skipped %llu bytes (resuming at 0x%08llx)",
+        (unsigned long long) bytes, (unsigned long long) offset);
     printCentered(4, 80, body);
 }
 
@@ -610,7 +612,8 @@ void process() {
     /* print summary on errors */
     if (num_errors) {
         printf("\n");
-        printf("Total unprocessable opcodes: %llu\n", num_errors);
+        printf("Total unprocessable opcodes: %llu\n",
+            (unsigned long long) num_errors);
     }
 }
 