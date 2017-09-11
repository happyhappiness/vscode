@@ -370,8 +370,8 @@ size_t zipmapBlobLen(unsigned char *zm) {
     return totlen;
 }
 
-#ifdef ZIPMAP_TEST_MAIN
-void zipmapRepr(unsigned char *p) {
+#ifdef REDIS_TEST
+static void zipmapRepr(unsigned char *p) {
     unsigned int l;
 
     printf("{status %u}",*p++);
@@ -404,9 +404,13 @@ void zipmapRepr(unsigned char *p) {
     printf("\n");
 }
 
-int main(void) {
+#define UNUSED(x) (void)(x)
+int zipmapTest(int argc, char *argv[]) {
     unsigned char *zm;
 
+    UNUSED(argc);
+    UNUSED(argv);
+
     zm = zipmapNew();
 
     zm = zipmapSet(zm,(unsigned char*) "name",4, (unsigned char*) "foo",3,NULL);