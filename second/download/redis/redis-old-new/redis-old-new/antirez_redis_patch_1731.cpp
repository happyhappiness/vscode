@@ -33,6 +33,7 @@
 #include <string.h>
 #include <pthread.h>
 #include "config.h"
+#include "zmalloc.h"
 
 #ifdef HAVE_MALLOC_SIZE
 #define PREFIX_SIZE (0)
@@ -52,19 +53,22 @@
 #define free(ptr) tc_free(ptr)
 #endif
 
-#define increment_used_memory(__n) do { \
+#define update_zmalloc_stat_alloc(__n,__size) do { \
     size_t _n = (__n); \
+    size_t _stat_slot = (__size < ZMALLOC_MAX_ALLOC_STAT) ? __size : ZMALLOC_MAX_ALLOC_STAT; \
     if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \
     if (zmalloc_thread_safe) { \
         pthread_mutex_lock(&used_memory_mutex);  \
         used_memory += _n; \
+        zmalloc_allocations[_stat_slot]++; \
         pthread_mutex_unlock(&used_memory_mutex); \
     } else { \
         used_memory += _n; \
+        zmalloc_allocations[_stat_slot]++; \
     } \
 } while(0)
 
-#define decrement_used_memory(__n) do { \
+#define update_zmalloc_stat_free(__n) do { \
     size_t _n = (__n); \
     if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \
     if (zmalloc_thread_safe) { \
@@ -79,6 +83,8 @@
 static size_t used_memory = 0;
 static int zmalloc_thread_safe = 0;
 pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;
+/* Note that malloc_allocations elements are initialized to zero by C */
+size_t zmalloc_allocations[ZMALLOC_MAX_ALLOC_STAT+1];
 
 static void zmalloc_oom(size_t size) {
     fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
@@ -92,11 +98,11 @@ void *zmalloc(size_t size) {
 
     if (!ptr) zmalloc_oom(size);
 #ifdef HAVE_MALLOC_SIZE
-    increment_used_memory(redis_malloc_size(ptr));
+    update_zmalloc_stat_alloc(redis_malloc_size(ptr),size);
     return ptr;
 #else
     *((size_t*)ptr) = size;
-    increment_used_memory(size+PREFIX_SIZE);
+    update_zmalloc_stat_alloc(size+PREFIX_SIZE,size);
     return (char*)ptr+PREFIX_SIZE;
 #endif
 }
@@ -106,11 +112,11 @@ void *zcalloc(size_t size) {
 
     if (!ptr) zmalloc_oom(size);
 #ifdef HAVE_MALLOC_SIZE
-    increment_used_memory(redis_malloc_size(ptr));
+    update_zmalloc_stat_alloc(redis_malloc_size(ptr),size);
     return ptr;
 #else
     *((size_t*)ptr) = size;
-    increment_used_memory(size+PREFIX_SIZE);
+    update_zmalloc_stat_alloc(size+PREFIX_SIZE,size);
     return (char*)ptr+PREFIX_SIZE;
 #endif
 }
@@ -128,8 +134,8 @@ void *zrealloc(void *ptr, size_t size) {
     newptr = realloc(ptr,size);
     if (!newptr) zmalloc_oom(size);
 
-    decrement_used_memory(oldsize);
-    increment_used_memory(redis_malloc_size(newptr));
+    update_zmalloc_stat_free(oldsize);
+    update_zmalloc_stat_alloc(redis_malloc_size(newptr),size);
     return newptr;
 #else
     realptr = (char*)ptr-PREFIX_SIZE;
@@ -138,8 +144,8 @@ void *zrealloc(void *ptr, size_t size) {
     if (!newptr) zmalloc_oom(size);
 
     *((size_t*)newptr) = size;
-    decrement_used_memory(oldsize);
-    increment_used_memory(size);
+    update_zmalloc_stat_free(oldsize);
+    update_zmalloc_stat_alloc(size,size);
     return (char*)newptr+PREFIX_SIZE;
 #endif
 }
@@ -152,12 +158,12 @@ void zfree(void *ptr) {
 
     if (ptr == NULL) return;
 #ifdef HAVE_MALLOC_SIZE
-    decrement_used_memory(redis_malloc_size(ptr));
+    update_zmalloc_stat_free(redis_malloc_size(ptr));
     free(ptr);
 #else
     realptr = (char*)ptr-PREFIX_SIZE;
     oldsize = *((size_t*)realptr);
-    decrement_used_memory(oldsize+PREFIX_SIZE);
+    update_zmalloc_stat_free(oldsize+PREFIX_SIZE);
     free(realptr);
 #endif
 }
@@ -179,6 +185,11 @@ size_t zmalloc_used_memory(void) {
     return um;
 }
 
+size_t zmalloc_allocations_for_size(size_t size) {
+    if (size > ZMALLOC_MAX_ALLOC_STAT || size < 0) return 0;
+    return zmalloc_allocations[size];
+}
+
 void zmalloc_enable_thread_safeness(void) {
     zmalloc_thread_safe = 1;
 }