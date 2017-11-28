     while (ptr <= end) {
         void *p = *(void **) ptr;
 
         if (p && p != start) {
             B = DBG_HASH_BUCKET(p);
 
-            for (I = 0; I < DBG_ARRY_SZ; I++) {
+            for (I = 0; I < DBG_ARRY_SZ; ++I) {
                 if (malloc_ptrs[B][I] == p) {
                     if (!malloc_refs[B][I]++) {
                         /* A new reference */
                         fprintf(stderr, "%*s%p %s:%d size %d allocation %d\n",
                                 depth, "",
                                 malloc_ptrs[B][I], malloc_file[B][I],
