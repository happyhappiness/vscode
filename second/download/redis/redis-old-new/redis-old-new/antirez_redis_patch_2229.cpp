@@ -31,6 +31,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <pthread.h>
 #include "config.h"
 
 #if defined(__sun)
@@ -40,6 +41,7 @@
 #endif
 
 static size_t used_memory = 0;
+pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;
 
 static void zmalloc_oom(size_t size) {
     fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",