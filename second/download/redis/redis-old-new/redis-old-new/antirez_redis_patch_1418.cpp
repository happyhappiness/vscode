@@ -28,18 +28,18 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
-#define SDS_ABORT_ON_OOM
-
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <ctype.h>
 #include "sds.h"
 
+#ifdef SDS_ABORT_ON_OOM
 static void sdsOomAbort(void) {
     fprintf(stderr,"SDS: Out Of Memory (SDS_ABORT_ON_OOM defined)\n");
     abort();
 }
+#endif
 
 sds sdsnewlen(const void *init, size_t initlen) {
     struct sdshdr *sh;
@@ -378,17 +378,19 @@ sds sdsfromlonglong(long long value) {
 
 sds sdscatrepr(sds s, char *p, size_t len) {
     s = sdscatlen(s,"\"",1);
+    if (s == NULL) return NULL;
+
     while(len--) {
         switch(*p) {
         case '\\':
         case '"':
             s = sdscatprintf(s,"\\%c",*p);
             break;
-        case '\n': s = sdscatlen(s,"\\n",1); break;
-        case '\r': s = sdscatlen(s,"\\r",1); break;
-        case '\t': s = sdscatlen(s,"\\t",1); break;
-        case '\a': s = sdscatlen(s,"\\a",1); break;
-        case '\b': s = sdscatlen(s,"\\b",1); break;
+        case '\n': s = sdscatlen(s,"\\n",2); break;
+        case '\r': s = sdscatlen(s,"\\r",2); break;
+        case '\t': s = sdscatlen(s,"\\t",2); break;
+        case '\a': s = sdscatlen(s,"\\a",2); break;
+        case '\b': s = sdscatlen(s,"\\b",2); break;
         default:
             if (isprint(*p))
                 s = sdscatprintf(s,"%c",*p);
@@ -397,6 +399,7 @@ sds sdscatrepr(sds s, char *p, size_t len) {
             break;
         }
         p++;
+        if (s == NULL) return NULL;
     }
     return sdscatlen(s,"\"",1);
 }
@@ -416,7 +419,7 @@ sds sdscatrepr(sds s, char *p, size_t len) {
 sds *sdssplitargs(char *line, int *argc) {
     char *p = line;
     char *current = NULL;
-    char **vector = NULL;
+    char **vector = NULL, **_vector = NULL;
 
     *argc = 0;
     while(1) {
@@ -427,7 +430,11 @@ sds *sdssplitargs(char *line, int *argc) {
             int inq=0; /* set to 1 if we are in "quotes" */
             int done=0;
 
-            if (current == NULL) current = sdsempty();
+            if (current == NULL) {
+                current = sdsempty();
+                if (current == NULL) goto err;
+            }
+
             while(!done) {
                 if (inq) {
                     if (*p == '\\' && *(p+1)) {
@@ -471,9 +478,13 @@ sds *sdssplitargs(char *line, int *argc) {
                     }
                 }
                 if (*p) p++;
+                if (current == NULL) goto err;
             }
             /* add the token to the vector */
-            vector = realloc(vector,((*argc)+1)*sizeof(char*));
+            _vector = realloc(vector,((*argc)+1)*sizeof(char*));
+            if (_vector == NULL) goto err;
+
+            vector = _vector;
             vector[*argc] = current;
             (*argc)++;
             current = NULL;
@@ -485,8 +496,8 @@ sds *sdssplitargs(char *line, int *argc) {
 err:
     while((*argc)--)
         sdsfree(vector[*argc]);
-    free(vector);
-    if (current) sdsfree(current);
+    if (vector != NULL) free(vector);
+    if (current != NULL) sdsfree(current);
     return NULL;
 }
 