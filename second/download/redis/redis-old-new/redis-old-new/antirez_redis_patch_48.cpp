@@ -13,6 +13,9 @@ typedef struct tsd_init_head_s tsd_init_head_t;
 #endif
 
 typedef struct tsd_s tsd_t;
+typedef struct tsdn_s tsdn_t;
+
+#define	TSDN_NULL	((tsdn_t *)0)
 
 typedef enum {
 	tsd_state_uninitialized,
@@ -44,7 +47,8 @@ typedef enum {
  * The result is a set of generated functions, e.g.:
  *
  *   bool example_tsd_boot(void) {...}
- *   example_t *example_tsd_get() {...}
+ *   bool example_tsd_booted_get(void) {...}
+ *   example_t *example_tsd_get(bool init) {...}
  *   void example_tsd_set(example_t *val) {...}
  *
  * Note that all of the functions deal in terms of (a_type *) rather than
@@ -98,8 +102,10 @@ a_attr void								\
 a_name##tsd_boot1(void);						\
 a_attr bool								\
 a_name##tsd_boot(void);							\
+a_attr bool								\
+a_name##tsd_booted_get(void);						\
 a_attr a_type *								\
-a_name##tsd_get(void);							\
+a_name##tsd_get(bool init);						\
 a_attr void								\
 a_name##tsd_set(a_type *val);
 
@@ -201,9 +207,21 @@ a_name##tsd_boot(void)							\
 									\
 	return (a_name##tsd_boot0());					\
 }									\
+a_attr bool								\
+a_name##tsd_booted_get(void)						\
+{									\
+									\
+	return (a_name##tsd_booted);					\
+}									\
+a_attr bool								\
+a_name##tsd_get_allocates(void)						\
+{									\
+									\
+	return (false);							\
+}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(void)							\
+a_name##tsd_get(bool init)						\
 {									\
 									\
 	assert(a_name##tsd_booted);					\
@@ -246,9 +264,21 @@ a_name##tsd_boot(void)							\
 									\
 	return (a_name##tsd_boot0());					\
 }									\
+a_attr bool								\
+a_name##tsd_booted_get(void)						\
+{									\
+									\
+	return (a_name##tsd_booted);					\
+}									\
+a_attr bool								\
+a_name##tsd_get_allocates(void)						\
+{									\
+									\
+	return (false);							\
+}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(void)							\
+a_name##tsd_get(bool init)						\
 {									\
 									\
 	assert(a_name##tsd_booted);					\
@@ -307,14 +337,14 @@ a_name##tsd_wrapper_set(a_name##tsd_wrapper_t *wrapper)			\
 	}								\
 }									\
 a_attr a_name##tsd_wrapper_t *						\
-a_name##tsd_wrapper_get(void)						\
+a_name##tsd_wrapper_get(bool init)					\
 {									\
 	DWORD error = GetLastError();					\
 	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)	\
 	    TlsGetValue(a_name##tsd_tsd);				\
 	SetLastError(error);						\
 									\
-	if (unlikely(wrapper == NULL)) {				\
+	if (init && unlikely(wrapper == NULL)) {			\
 		wrapper = (a_name##tsd_wrapper_t *)			\
 		    malloc_tsd_malloc(sizeof(a_name##tsd_wrapper_t));	\
 		if (wrapper == NULL) {					\
@@ -368,14 +398,28 @@ a_name##tsd_boot(void)							\
 	a_name##tsd_boot1();						\
 	return (false);							\
 }									\
+a_attr bool								\
+a_name##tsd_booted_get(void)						\
+{									\
+									\
+	return (a_name##tsd_booted);					\
+}									\
+a_attr bool								\
+a_name##tsd_get_allocates(void)						\
+{									\
+									\
+	return (true);							\
+}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(void)							\
+a_name##tsd_get(bool init)						\
 {									\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get();				\
+	wrapper = a_name##tsd_wrapper_get(init);			\
+	if (a_name##tsd_get_allocates() && !init && wrapper == NULL)	\
+		return (NULL);						\
 	return (&wrapper->val);						\
 }									\
 a_attr void								\
@@ -384,7 +428,7 @@ a_name##tsd_set(a_type *val)						\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get();				\
+	wrapper = a_name##tsd_wrapper_get(true);			\
 	wrapper->val = *(val);						\
 	if (a_cleanup != malloc_tsd_no_cleanup)				\
 		wrapper->initialized = true;				\
@@ -428,12 +472,12 @@ a_name##tsd_wrapper_set(a_name##tsd_wrapper_t *wrapper)			\
 	}								\
 }									\
 a_attr a_name##tsd_wrapper_t *						\
-a_name##tsd_wrapper_get(void)						\
+a_name##tsd_wrapper_get(bool init)					\
 {									\
 	a_name##tsd_wrapper_t *wrapper = (a_name##tsd_wrapper_t *)	\
 	    pthread_getspecific(a_name##tsd_tsd);			\
 									\
-	if (unlikely(wrapper == NULL)) {				\
+	if (init && unlikely(wrapper == NULL)) {			\
 		tsd_init_block_t block;					\
 		wrapper = tsd_init_check_recursion(			\
 		    &a_name##tsd_init_head, &block);			\
@@ -490,14 +534,28 @@ a_name##tsd_boot(void)							\
 	a_name##tsd_boot1();						\
 	return (false);							\
 }									\
+a_attr bool								\
+a_name##tsd_booted_get(void)						\
+{									\
+									\
+	return (a_name##tsd_booted);					\
+}									\
+a_attr bool								\
+a_name##tsd_get_allocates(void)						\
+{									\
+									\
+	return (true);							\
+}									\
 /* Get/set. */								\
 a_attr a_type *								\
-a_name##tsd_get(void)							\
+a_name##tsd_get(bool init)						\
 {									\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get();				\
+	wrapper = a_name##tsd_wrapper_get(init);			\
+	if (a_name##tsd_get_allocates() && !init && wrapper == NULL)	\
+		return (NULL);						\
 	return (&wrapper->val);						\
 }									\
 a_attr void								\
@@ -506,7 +564,7 @@ a_name##tsd_set(a_type *val)						\
 	a_name##tsd_wrapper_t *wrapper;					\
 									\
 	assert(a_name##tsd_booted);					\
-	wrapper = a_name##tsd_wrapper_get();				\
+	wrapper = a_name##tsd_wrapper_get(true);			\
 	wrapper->val = *(val);						\
 	if (a_cleanup != malloc_tsd_no_cleanup)				\
 		wrapper->initialized = true;				\
@@ -536,12 +594,15 @@ struct tsd_init_head_s {
     O(thread_allocated,		uint64_t)				\
     O(thread_deallocated,	uint64_t)				\
     O(prof_tdata,		prof_tdata_t *)				\
+    O(iarena,			arena_t *)				\
     O(arena,			arena_t *)				\
-    O(arenas_cache,		arena_t **)				\
-    O(narenas_cache,		unsigned)				\
-    O(arenas_cache_bypass,	bool)					\
+    O(arenas_tdata,		arena_tdata_t *)			\
+    O(narenas_tdata,		unsigned)				\
+    O(arenas_tdata_bypass,	bool)					\
     O(tcache_enabled,		tcache_enabled_t)			\
     O(quarantine,		quarantine_t *)				\
+    O(witnesses,		witness_list_t)				\
+    O(witness_fork,		bool)					\
 
 #define	TSD_INITIALIZER {						\
     tsd_state_uninitialized,						\
@@ -551,10 +612,13 @@ struct tsd_init_head_s {
     NULL,								\
     NULL,								\
     NULL,								\
+    NULL,								\
     0,									\
     false,								\
     tcache_enabled_default,						\
-    NULL								\
+    NULL,								\
+    ql_head_initializer(witnesses),					\
+    false								\
 }
 
 struct tsd_s {
@@ -565,6 +629,15 @@ MALLOC_TSD
 #undef O
 };
 
+/*
+ * Wrapper around tsd_t that makes it possible to avoid implicit conversion
+ * between tsd_t and tsdn_t, where tsdn_t is "nullable" and has to be
+ * explicitly converted to tsd_t, which is non-nullable.
+ */
+struct tsdn_s {
+	tsd_t	tsd;
+};
+
 static const tsd_t tsd_initializer = TSD_INITIALIZER;
 
 malloc_tsd_types(, tsd_t)
@@ -577,7 +650,7 @@ void	*malloc_tsd_malloc(size_t size);
 void	malloc_tsd_dalloc(void *wrapper);
 void	malloc_tsd_no_cleanup(void *arg);
 void	malloc_tsd_cleanup_register(bool (*f)(void));
-bool	malloc_tsd_boot0(void);
+tsd_t	*malloc_tsd_boot0(void);
 void	malloc_tsd_boot1(void);
 #if (!defined(JEMALLOC_MALLOC_THREAD_CLEANUP) && !defined(JEMALLOC_TLS) && \
     !defined(_WIN32))
@@ -594,24 +667,33 @@ void	tsd_cleanup(void *arg);
 #ifndef JEMALLOC_ENABLE_INLINE
 malloc_tsd_protos(JEMALLOC_ATTR(unused), , tsd_t)
 
+tsd_t	*tsd_fetch_impl(bool init);
 tsd_t	*tsd_fetch(void);
+tsdn_t	*tsd_tsdn(tsd_t *tsd);
 bool	tsd_nominal(tsd_t *tsd);
 #define	O(n, t)								\
 t	*tsd_##n##p_get(tsd_t *tsd);					\
 t	tsd_##n##_get(tsd_t *tsd);					\
 void	tsd_##n##_set(tsd_t *tsd, t n);
 MALLOC_TSD
 #undef O
+tsdn_t	*tsdn_fetch(void);
+bool	tsdn_null(const tsdn_t *tsdn);
+tsd_t	*tsdn_tsd(tsdn_t *tsdn);
 #endif
 
 #if (defined(JEMALLOC_ENABLE_INLINE) || defined(JEMALLOC_TSD_C_))
 malloc_tsd_externs(, tsd_t)
 malloc_tsd_funcs(JEMALLOC_ALWAYS_INLINE, , tsd_t, tsd_initializer, tsd_cleanup)
 
 JEMALLOC_ALWAYS_INLINE tsd_t *
-tsd_fetch(void)
+tsd_fetch_impl(bool init)
 {
-	tsd_t *tsd = tsd_get();
+	tsd_t *tsd = tsd_get(init);
+
+	if (!init && tsd_get_allocates() && tsd == NULL)
+		return (NULL);
+	assert(tsd != NULL);
 
 	if (unlikely(tsd->state != tsd_state_nominal)) {
 		if (tsd->state == tsd_state_uninitialized) {
@@ -628,6 +710,20 @@ tsd_fetch(void)
 	return (tsd);
 }
 
+JEMALLOC_ALWAYS_INLINE tsd_t *
+tsd_fetch(void)
+{
+
+	return (tsd_fetch_impl(true));
+}
+
+JEMALLOC_ALWAYS_INLINE tsdn_t *
+tsd_tsdn(tsd_t *tsd)
+{
+
+	return ((tsdn_t *)tsd);
+}
+
 JEMALLOC_INLINE bool
 tsd_nominal(tsd_t *tsd)
 {
@@ -659,6 +755,32 @@ tsd_##n##_set(tsd_t *tsd, t n)						\
 }
 MALLOC_TSD
 #undef O
+
+JEMALLOC_ALWAYS_INLINE tsdn_t *
+tsdn_fetch(void)
+{
+
+	if (!tsd_booted_get())
+		return (NULL);
+
+	return (tsd_tsdn(tsd_fetch_impl(false)));
+}
+
+JEMALLOC_ALWAYS_INLINE bool
+tsdn_null(const tsdn_t *tsdn)
+{
+
+	return (tsdn == NULL);
+}
+
+JEMALLOC_ALWAYS_INLINE tsd_t *
+tsdn_tsd(tsdn_t *tsdn)
+{
+
+	assert(!tsdn_null(tsdn));
+
+	return (&tsdn->tsd);
+}
 #endif
 
 #endif /* JEMALLOC_H_INLINES */