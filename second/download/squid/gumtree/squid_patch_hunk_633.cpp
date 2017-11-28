             perror("realloc");
         }
 
         exit(1);
     }
 
-#if XMALLOC_DEBUG
-    check_malloc(p, sz);
-#endif
 #if XMALLOC_STATISTICS
     malloc_stat(sz);
 #endif
-#if MEM_GEN_TRACE
-    if (tracefp)                /* new ptr, old ptr, new size */
-        fprintf(tracefp, "r:%p:%p:%d\n", p, s, sz);
-#endif
+
     PROF_stop(xrealloc);
     return (p);
 }
 
 void
 free_const(const void *s_const)
 {
     void *s = const_cast<void *>(s_const);
 
     PROF_start(free_const);
-
-#if XMALLOC_DEBUG
-    check_free(s);
-#endif
-
     PROF_start(free);
     free(s);
     PROF_stop(free);
-
-#if MEM_GEN_TRACE
-    if (tracefp)
-        fprintf(tracefp, "f:%p\n", s);
-#endif
     PROF_stop(free_const);
 }
+
