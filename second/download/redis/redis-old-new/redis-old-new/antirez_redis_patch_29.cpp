@@ -13,9 +13,6 @@ typedef struct tsd_init_head_s tsd_init_head_t;
 #endif
 
 typedef struct tsd_s tsd_t;
-typedef struct tsdn_s tsdn_t;
-
-#define	TSDN_NULL	((tsdn_t *)0)
 
 typedef enum {
 	tsd_state_uninitialized,
@@ -47,8 +44,7 @@ typedef enum {
  * The result is a set of generated functions, e.g.:
  *
  *   bool example_tsd_boot(void) {...}
- *   bool example_tsd_booted_get(void) {...}
- *   example_t *example_tsd_get(bool init) {...}
+ *   example_t *example_tsd_get() {...}
  *   void example_tsd_set(example_t *val) {...}
  *
  * Note that all of the functions deal in terms of (a_type *) rather than
@@ -102,10 +98,8 @@ a_attr void								\
 a_name##tsd_boot1(void);						\
 a_attr bool								\
 a_name##tsd_boot(void);							\
-a_attr bool								\
-a_name##tsd_booted_get(void);						\
 a_attr a_type *								\
-a_name##tsd_get(bool init);						\
+a_name##tsd_get(void);							\
 a_attr void								\
 a_name##tsd_set(a_type *val);
 
@@ -207,21 +201,9 @@ a_name##tsd_boot(void)							\
 									\
 	return (a_name##tsd_boot0());					\
 }									\
-a_attr bool								\
-a_name##tsd_booted_get(void)						\
-{									\
-									\
-	return (a_name##tsd_booted);					\
-}									\
-a_attr bool								\
-a_name##tsd_get_allocates(void)						\
-{									\
-									\
-	return (false);							\
-}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(bool init)						\
+a_name##tsd_get(void)							\
 {									\
 									\
 	assert(a_name##tsd_booted);					\
@@ -264,21 +246,9 @@ a_name##tsd_boot(void)							\
 									\
 	return (a_name##tsd_boot0());					\
 }									\
-a_attr bool								\
-a_name##tsd_booted_get(void)						\
-{									\
-									\
-	return (a_name##tsd_booted);					\
-}									\
-a_attr bool								\
-a_name##tsd_get_allocates(void)						\
-{									\
-									\
-	return (false);							\
-}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(bool init)						\
+a_name##tsd_get(void)							\
 {									\
 									\
 	assert(a_name##tsd_booted);					\
@@ -337,14 +307,14 @@ a_name##tsd_wrapper_set(a_name##tsd_wrapper_t *wrapper)			\
 	}								\
 }									\
 a_attr a_name##tsd_wrapper_t *						\
-a_name##tsd_wrapper_get(bool init)					\
+a_name##tsd_wrapper_get(void)						\
 {									\
 	DWORD error = GetLastError();					\
 	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)	\
 	    TlsGetValue(a_name##tsd_tsd);				\
 	SetLastError(error);						\
 									\
-	if (init && unlikely(wrapper == NULL)) {			\
+	if (unlikely(wrapper == NULL)) {				\
 		wrapper = (a_name##tsd_wrapper_t *)			\
 		    malloc_tsd_malloc(sizeof(a_name##tsd_wrapper_t));	\
 		if (wrapper == NULL) {					\
@@ -398,28 +368,14 @@ a_name##tsd_boot(void)							\
 	a_name##tsd_boot1();						\
 	return (false);							\
 }									\
-a_attr bool								\
-a_name##tsd_booted_get(void)						\
-{									\
-									\
-	return (a_name##tsd_booted);					\
-}									\
-a_attr bool								\
-a_name##tsd_get_allocates(void)						\
-{									\
-									\
-	return (true);							\
-}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(bool init)						\
+a_name##tsd_get(void)							\
 {									\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get(init);			\
-	if (a_name##tsd_get_allocates() && !init && wrapper == NULL)	\
-		return (NULL);						\
+	wrapper = a_name##tsd_wrapper_get();				\
 	return (&wrapper->val);						\
 }									\
 a_attr void								\
@@ -428,7 +384,7 @@ a_name##tsd_set(a_type *val)						\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get(true);			\
+	wrapper = a_name##tsd_wrapper_get();				\
 	wrapper->val = *(val);						\
 	if (a_cleanup != malloc_tsd_no_cleanup)				\
 		wrapper->initialized = true;				\
@@ -472,12 +428,12 @@ a_name##tsd_wrapper_set(a_name##tsd_wrapper_t *wrapper)			\
 	}								\
 }									\
 a_attr a_name##tsd_wrapper_t *						\
-a_name##tsd_wrapper_get(bool init)					\
+a_name##tsd_wrapper_get(void)						\
 {									\
 	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)	\
 	    pthread_getspecific(a_name##tsd_tsd);			\
 									\
-	if (init && unlikely(wrapper == NULL)) {			\
+	if (unlikely(wrapper == NULL)) {				\
 		tsd_init_block_t block;					\
 		wrapper = tsd_init_check_recursion(			\
 		    &a_name##tsd_init_head, &block);			\
@@ -534,28 +490,14 @@ a_name##tsd_boot(void)							\
 	a_name##tsd_boot1();						\
 	return (false);							\
 }									\
-a_attr bool								\
-a_name##tsd_booted_get(void)						\
-{									\
-									\
-	return (a_name##tsd_booted);					\
-}									\
-a_attr bool								\
-a_name##tsd_get_allocates(void)						\
-{									\
-									\
-	return (true);							\
-}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(bool init)						\
+a_name##tsd_get(void)							\
 {									\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get(init);			\
-	if (a_name##tsd_get_allocates() && !init && wrapper == NULL)	\
-		return (NULL);						\
+	wrapper = a_name##tsd_wrapper_get();				\
 	return (&wrapper->val);						\
 }									\
 a_attr void								\
@@ -564,7 +506,7 @@ a_name##tsd_set(a_type *val)						\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get(true);			\
+	wrapper = a_name##tsd_wrapper_get();				\
 	wrapper->val = *(val);						\
 	if (a_cleanup != malloc_tsd_no_cleanup)				\
 		wrapper->initialized = true;				\
@@ -594,15 +536,12 @@ struct tsd_init_head_s {
     O(thread_allocated,		uint64_t)				\
     O(thread_deallocated,	uint64_t)				\
     O(prof_tdata,		prof_tdata_t *)				\
-    O(iarena,			arena_t *)				\
     O(arena,			arena_t *)				\
-    O(arenas_tdata,		arena_tdata_t *)			\
-    O(narenas_tdata,		unsigned)				\
-    O(arenas_tdata_bypass,	bool)					\
+    O(arenas_cache,		arena_t **)				\
+    O(narenas_cache,		unsigned)				\
+    O(arenas_cache_bypass,	bool)					\
     O(tcache_enabled,		tcache_enabled_t)			\
     O(quarantine,		quarantine_t *)				\
-    O(witnesses,		witness_list_t)				\
-    O(witness_fork,		bool)					\
 
 #define	TSD_INITIALIZER {						\
     tsd_state_uninitialized,						\
@@ -612,13 +551,10 @@ struct tsd_init_head_s {
     NULL,								\
     NULL,								\
     NULL,								\
-    NULL,								\
     0,									\
     false,								\
     tcache_enabled_default,						\
-    NULL,								\
-    ql_head_initializer(witnesses),					\
-    false								\
+    NULL								\
 }
 
 struct tsd_s {
@@ -629,15 +565,6 @@ MALLOC_TSD
 #undef O
 };
 
-/*
- * Wrapper around tsd_t that makes it possible to avoid implicit conversion
- * between tsd_t and tsdn_t, where tsdn_t is "nullable" and has to be
- * explicitly converted to tsd_t, which is non-nullable.
- */
-struct tsdn_s {
-	tsd_t	tsd;
-};
-
 static const tsd_t tsd_initializer = TSD_INITIALIZER;
 
 malloc_tsd_types(, tsd_t)
@@ -650,7 +577,7 @@ void	*malloc_tsd_malloc(size_t size);
 void	malloc_tsd_dalloc(void *wrapper);
 void	malloc_tsd_no_cleanup(void *arg);
 void	malloc_tsd_cleanup_register(bool (*f)(void));
-tsd_t	*malloc_tsd_boot0(void);
+bool	malloc_tsd_boot0(void);
 void	malloc_tsd_boot1(void);
 #if (!defined(JEMALLOC_MALLOC_THREAD_CLEANUP) && !defined(JEMALLOC_TLS) && \
     !defined(_WIN32))
@@ -667,33 +594,24 @@ void	tsd_cleanup(void *arg);
 #ifndef JEMALLOC_ENABLE_INLINE
 malloc_tsd_protos(JEMALLOC_ATTR(unused), , tsd_t)
 
-tsd_t	*tsd_fetch_impl(bool init);
 tsd_t	*tsd_fetch(void);
-tsdn_t	*tsd_tsdn(tsd_t *tsd);
 bool	tsd_nominal(tsd_t *tsd);
 #define	O(n, t)								\
 t	*tsd_##n##p_get(tsd_t *tsd);					\
 t	tsd_##n##_get(tsd_t *tsd);					\
 void	tsd_##n##_set(tsd_t *tsd, t n);
 MALLOC_TSD
 #undef O
-tsdn_t	*tsdn_fetch(void);
-bool	tsdn_null(const tsdn_t *tsdn);
-tsd_t	*tsdn_tsd(tsdn_t *tsdn);
 #endif
 
 #if (defined(JEMALLOC_ENABLE_INLINE) || defined(JEMALLOC_TSD_C_))
 malloc_tsd_externs(, tsd_t)
 malloc_tsd_funcs(JEMALLOC_ALWAYS_INLINE, , tsd_t, tsd_initializer, tsd_cleanup)
 
 JEMALLOC_ALWAYS_INLINE tsd_t *
-tsd_fetch_impl(bool init)
+tsd_fetch(void)
 {
-	tsd_t *tsd = tsd_get(init);
-
-	if (!init && tsd_get_allocates() && tsd == NULL)
-		return (NULL);
-	assert(tsd != NULL);
+	tsd_t *tsd = tsd_get();
 
 	if (unlikely(tsd->state != tsd_state_nominal)) {
 		if (tsd->state == tsd_state_uninitialized) {
@@ -710,20 +628,6 @@ tsd_fetch_impl(bool init)
 	return (tsd);
 }
 
-JEMALLOC_ALWAYS_INLINE tsd_t *
-tsd_fetch(void)
-{
-
-	return (tsd_fetch_impl(true));
-}
-
-JEMALLOC_ALWAYS_INLINE tsdn_t *
-tsd_tsdn(tsd_t *tsd)
-{
-
-	return ((tsdn_t *)tsd);
-}
-
 JEMALLOC_INLINE bool
 tsd_nominal(tsd_t *tsd)
 {
@@ -755,32 +659,6 @@ tsd_##n##_set(tsd_t *tsd, t n)						\
 }
 MALLOC_TSD
 #undef O
-
-JEMALLOC_ALWAYS_INLINE tsdn_t *
-tsdn_fetch(void)
-{
-
-	if (!tsd_booted_get())
-		return (NULL);
-
-	return (tsd_tsdn(tsd_fetch_impl(false)));
-}
-
-JEMALLOC_ALWAYS_INLINE bool
-tsdn_null(const tsdn_t *tsdn)
-{
-
-	return (tsdn == NULL);
-}
-
-JEMALLOC_ALWAYS_INLINE tsd_t *
-tsdn_tsd(tsdn_t *tsdn)
-{
-
-	assert(!tsdn_null(tsdn));
-
-	return (&tsdn->tsd);
-}
 #endif
 
 #endif /* JEMALLOC_H_INLINES */