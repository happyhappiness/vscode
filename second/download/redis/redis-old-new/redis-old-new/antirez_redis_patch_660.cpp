@@ -952,14 +952,14 @@ void ziplistRepr(unsigned char *zl) {
     printf("{end}\n\n");
 }
 
-#ifdef ZIPLIST_TEST_MAIN
+#ifdef REDIS_TEST
 #include <sys/time.h>
 #include "adlist.h"
 #include "sds.h"
 
 #define debug(f, ...) { if (DEBUG) printf(f, __VA_ARGS__); }
 
-unsigned char *createList() {
+static unsigned char *createList() {
     unsigned char *zl = ziplistNew();
     zl = ziplistPush(zl, (unsigned char*)"foo", 3, ZIPLIST_TAIL);
     zl = ziplistPush(zl, (unsigned char*)"quux", 4, ZIPLIST_TAIL);
@@ -968,7 +968,7 @@ unsigned char *createList() {
     return zl;
 }
 
-unsigned char *createIntList() {
+static unsigned char *createIntList() {
     unsigned char *zl = ziplistNew();
     char buf[32];
 
@@ -987,13 +987,13 @@ unsigned char *createIntList() {
     return zl;
 }
 
-long long usec(void) {
+static long long usec(void) {
     struct timeval tv;
     gettimeofday(&tv,NULL);
     return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
 }
 
-void stress(int pos, int num, int maxsize, int dnum) {
+static void stress(int pos, int num, int maxsize, int dnum) {
     int i,j,k;
     unsigned char *zl;
     char posstr[2][5] = { "HEAD", "TAIL" };
@@ -1016,7 +1016,7 @@ void stress(int pos, int num, int maxsize, int dnum) {
     }
 }
 
-void pop(unsigned char *zl, int where) {
+static void pop(unsigned char *zl, int where) {
     unsigned char *p, *vstr;
     unsigned int vlen;
     long long vlong;
@@ -1043,7 +1043,7 @@ void pop(unsigned char *zl, int where) {
     }
 }
 
-int randstring(char *target, unsigned int min, unsigned int max) {
+static int randstring(char *target, unsigned int min, unsigned int max) {
     int p = 0;
     int len = min+rand()%(max-min+1);
     int minval, maxval;
@@ -1069,7 +1069,7 @@ int randstring(char *target, unsigned int min, unsigned int max) {
     return len;
 }
 
-void verify(unsigned char *zl, zlentry *e) {
+static void verify(unsigned char *zl, zlentry *e) {
     int i;
     int len = ziplistLen(zl);
     zlentry _e;
@@ -1085,7 +1085,7 @@ void verify(unsigned char *zl, zlentry *e) {
     }
 }
 
-int main(int argc, char **argv) {
+int ziplistTest(int argc, char **argv) {
     unsigned char *zl, *p;
     unsigned char *entry;
     unsigned int elen;
@@ -1534,5 +1534,4 @@ int main(int argc, char **argv) {
 
     return 0;
 }
-
 #endif