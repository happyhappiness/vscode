 /*
  * Size of stack-allocated buffer used by malloc_{,v,vc}printf().  This must be
  * large enough for all possible uses within jemalloc.
  */
 #define	MALLOC_PRINTF_BUFSIZE	4096
 
-/* Junk fill patterns. */
-#ifndef JEMALLOC_ALLOC_JUNK
-#  define JEMALLOC_ALLOC_JUNK	((uint8_t)0xa5)
-#endif
-#ifndef JEMALLOC_FREE_JUNK
-#  define JEMALLOC_FREE_JUNK	((uint8_t)0x5a)
-#endif
-
 /*
  * Wrap a cpp argument that contains commas such that it isn't broken up into
  * multiple arguments.
  */
 #define	JEMALLOC_ARG_CONCAT(...) __VA_ARGS__
 
