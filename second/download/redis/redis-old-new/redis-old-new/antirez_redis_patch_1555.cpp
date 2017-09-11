@@ -60,16 +60,13 @@
 
 #define update_zmalloc_stat_alloc(__n,__size) do { \
     size_t _n = (__n); \
-    size_t _stat_slot = (__size < ZMALLOC_MAX_ALLOC_STAT) ? __size : ZMALLOC_MAX_ALLOC_STAT; \
     if (_n&(sizeof(long)-1)) _n += sizeof(long)-(_n&(sizeof(long)-1)); \
     if (zmalloc_thread_safe) { \
         pthread_mutex_lock(&used_memory_mutex);  \
         used_memory += _n; \
-        zmalloc_allocations[_stat_slot]++; \
         pthread_mutex_unlock(&used_memory_mutex); \
     } else { \
         used_memory += _n; \
-        zmalloc_allocations[_stat_slot]++; \
     } \
 } while(0)
 
@@ -88,8 +85,6 @@
 static size_t used_memory = 0;
 static int zmalloc_thread_safe = 0;
 pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;
-/* Note that malloc_allocations elements are initialized to zero by C */
-size_t zmalloc_allocations[ZMALLOC_MAX_ALLOC_STAT+1];
 
 static void zmalloc_oom(size_t size) {
     fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
@@ -190,11 +185,6 @@ size_t zmalloc_used_memory(void) {
     return um;
 }
 
-size_t zmalloc_allocations_for_size(size_t size) {
-    if (size > ZMALLOC_MAX_ALLOC_STAT) return 0;
-    return zmalloc_allocations[size];
-}
-
 void zmalloc_enable_thread_safeness(void) {
     zmalloc_thread_safe = 1;
 }