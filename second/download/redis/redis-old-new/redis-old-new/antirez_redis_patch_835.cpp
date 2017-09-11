@@ -14,7 +14,7 @@
  * Wrap a cpp argument that contains commas such that it isn't broken up into
  * multiple arguments.
  */
-#define JEMALLOC_CONCAT(...) __VA_ARGS__
+#define	JEMALLOC_ARG_CONCAT(...) __VA_ARGS__
 
 /*
  * Silence compiler warnings due to uninitialized values.  This is used
@@ -42,12 +42,6 @@
 } while (0)
 #endif
 
-/* Use to assert a particular configuration, e.g., cassert(config_debug). */
-#define	cassert(c) do {							\
-	if ((c) == false)						\
-		assert(false);						\
-} while (0)
-
 #ifndef not_reached
 #define	not_reached() do {						\
 	if (config_debug) {						\
@@ -69,10 +63,18 @@
 } while (0)
 #endif
 
+#ifndef assert_not_implemented
 #define	assert_not_implemented(e) do {					\
 	if (config_debug && !(e))					\
 		not_implemented();					\
 } while (0)
+#endif
+
+/* Use to assert a particular configuration, e.g., cassert(config_debug). */
+#define	cassert(c) do {							\
+	if ((c) == false)						\
+		not_reached();						\
+} while (0)
 
 #endif /* JEMALLOC_H_TYPES */
 /******************************************************************************/
@@ -82,8 +84,9 @@
 /******************************************************************************/
 #ifdef JEMALLOC_H_EXTERNS
 
-int	buferror(char *buf, size_t buflen);
-uintmax_t	malloc_strtoumax(const char *nptr, char **endptr, int base);
+int	buferror(int err, char *buf, size_t buflen);
+uintmax_t	malloc_strtoumax(const char *restrict nptr,
+    char **restrict endptr, int base);
 void	malloc_write(const char *s);
 
 /*
@@ -107,7 +110,6 @@ void	malloc_printf(const char *format, ...)
 
 #ifndef JEMALLOC_ENABLE_INLINE
 size_t	pow2_ceil(size_t x);
-void	malloc_write(const char *s);
 void	set_errno(int errnum);
 int	get_errno(void);
 #endif