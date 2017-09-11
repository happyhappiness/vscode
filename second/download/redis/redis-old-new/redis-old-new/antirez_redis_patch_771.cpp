@@ -138,8 +138,10 @@ typedef struct {
  * at runtime to avoid strange compiler optimizations. */
 static double R_Zero, R_PosInf, R_NegInf, R_Nan;
 
+#define MAX_TYPES_NUM 256
+#define MAX_TYPE_NAME_LEN 16
 /* store string types for output */
-static char types[256][16];
+static char types[MAX_TYPES_NUM][MAX_TYPE_NAME_LEN];
 
 /* Return true if 't' is a valid object type. */
 int checkType(unsigned char t) {
@@ -166,7 +168,7 @@ int readBytes(void *target, long num) {
     return 1;
 }
 
-int processHeader() {
+int processHeader(void) {
     char buf[10] = "_________";
     int dump_version;
 
@@ -335,6 +337,7 @@ char* loadStringObject() {
     if (len == REDIS_RDB_LENERR) return NULL;
 
     char *buf = malloc(sizeof(char) * (len+1));
+    if (buf == NULL) return NULL;
     buf[len] = '\0';
     if (!readBytes(buf, len)) {
         free(buf);
@@ -600,7 +603,7 @@ void printErrorStack(entry *e) {
     }
 }
 
-void process() {
+void process(void) {
     uint64_t num_errors = 0, num_valid_ops = 0, num_valid_bytes = 0;
     entry entry;
     int dump_version = processHeader();
@@ -611,7 +614,7 @@ void process() {
             printf("RDB version >= 5 but no room for checksum.\n");
             exit(1);
         }
-        positions[0].size -= 8;;
+        positions[0].size -= 8;
     }
 
     level = 1;