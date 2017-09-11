@@ -162,6 +162,13 @@ typedef struct zlentry {
     unsigned char *p;
 } zlentry;
 
+#define ZIPLIST_ENTRY_ZERO(zle) { \
+    (zle)->prevrawlensize = (zle)->prevrawlen = 0; \
+    (zle)->lensize = (zle)->len = (zle)->headersize = 0; \
+    (zle)->encoding = 0; \
+    (zle)->p = NULL; \
+}
+
 /* Extract the encoding from the byte pointed by 'ptr' and set it into
  * 'encoding'. */
 #define ZIP_ENTRY_ENCODING(ptr, encoding) do {  \
@@ -1068,11 +1075,12 @@ static int randstring(char *target, unsigned int min, unsigned int max) {
 }
 
 static void verify(unsigned char *zl, zlentry *e) {
-    int i;
     int len = ziplistLen(zl);
     zlentry _e;
 
-    for (i = 0; i < len; i++) {
+    ZIPLIST_ENTRY_ZERO(&_e);
+
+    for (int i = 0; i < len; i++) {
         memset(&e[i], 0, sizeof(zlentry));
         zipEntry(ziplistIndex(zl, i), &e[i]);
 
@@ -1347,7 +1355,7 @@ int ziplistTest(int argc, char **argv) {
 
     printf("Regression test for >255 byte strings:\n");
     {
-        char v1[257],v2[257];
+        char v1[257] = {0}, v2[257] = {0};
         memset(v1,'x',256);
         memset(v2,'y',256);
         zl = ziplistNew();
@@ -1366,8 +1374,9 @@ int ziplistTest(int argc, char **argv) {
 
     printf("Regression test deleting next to last entries:\n");
     {
-        char v[3][257];
-        zlentry e[3];
+        char v[3][257] = {{0}};
+        zlentry e[3] = {{.prevrawlensize = 0, .prevrawlen = 0, .lensize = 0,
+                         .len = 0, .headersize = 0, .encoding = 0, .p = NULL}};
         size_t i;
 
         for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++) {