@@ -28,16 +28,24 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
+#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "config.h"
 
 static size_t used_memory = 0;
 
+static void zmalloc_oom(size_t size) {
+    fprintf(stderr, "zmalloc: Out of memory trying to allocate %lu bytes\n",
+        size);
+    fflush(stderr);
+    abort();
+}
+
 void *zmalloc(size_t size) {
     void *ptr = malloc(size+sizeof(size_t));
 
-    if (!ptr) return NULL;
+    if (!ptr) zmalloc_oom(size);
 #ifdef HAVE_MALLOC_SIZE
     used_memory += redis_malloc_size(ptr);
     return ptr;
@@ -59,7 +67,7 @@ void *zrealloc(void *ptr, size_t size) {
 #ifdef HAVE_MALLOC_SIZE
     oldsize = redis_malloc_size(ptr);
     newptr = realloc(ptr,size);
-    if (!newptr) return NULL;
+    if (!newptr) zmalloc_oom(size);
 
     used_memory -= oldsize;
     used_memory += redis_malloc_size(newptr);
@@ -68,7 +76,7 @@ void *zrealloc(void *ptr, size_t size) {
     realptr = (char*)ptr-sizeof(size_t);
     oldsize = *((size_t*)realptr);
     newptr = realloc(realptr,size+sizeof(size_t));
-    if (!newptr) return NULL;
+    if (!newptr) zmalloc_oom(size);
 
     *((size_t*)newptr) = size;
     used_memory -= oldsize;