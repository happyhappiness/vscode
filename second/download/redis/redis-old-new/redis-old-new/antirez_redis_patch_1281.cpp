@@ -109,17 +109,19 @@ static size_t used_memory = 0;
 static int zmalloc_thread_safe = 0;
 pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;
 
-static void zmalloc_oom(size_t size) {
+static void zmalloc_default_oom(size_t size) {
     fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
         size);
     fflush(stderr);
     abort();
 }
 
+static void (*zmalloc_oom_handler)(size_t) = zmalloc_default_oom;
+
 void *zmalloc(size_t size) {
     void *ptr = malloc(size+PREFIX_SIZE);
 
-    if (!ptr) zmalloc_oom(size);
+    if (!ptr) zmalloc_oom_handler(size);
 #ifdef HAVE_MALLOC_SIZE
     update_zmalloc_stat_alloc(zmalloc_size(ptr),size);
     return ptr;
@@ -133,7 +135,7 @@ void *zmalloc(size_t size) {
 void *zcalloc(size_t size) {
     void *ptr = calloc(1, size+PREFIX_SIZE);
 
-    if (!ptr) zmalloc_oom(size);
+    if (!ptr) zmalloc_oom_handler(size);
 #ifdef HAVE_MALLOC_SIZE
     update_zmalloc_stat_alloc(zmalloc_size(ptr),size);
     return ptr;
@@ -155,7 +157,7 @@ void *zrealloc(void *ptr, size_t size) {
 #ifdef HAVE_MALLOC_SIZE
     oldsize = zmalloc_size(ptr);
     newptr = realloc(ptr,size);
-    if (!newptr) zmalloc_oom(size);
+    if (!newptr) zmalloc_oom_handler(size);
 
     update_zmalloc_stat_free(oldsize);
     update_zmalloc_stat_alloc(zmalloc_size(newptr),size);
@@ -236,6 +238,10 @@ void zmalloc_enable_thread_safeness(void) {
     zmalloc_thread_safe = 1;
 }
 
+void zmalloc_set_oom_handler(void (*oom_handler)(size_t)) {
+    zmalloc_oom_handler = oom_handler;
+}
+
 /* Get the RSS information in an OS-specific way.
  *
  * WARNING: the function zmalloc_get_rss() is not designed to be fast