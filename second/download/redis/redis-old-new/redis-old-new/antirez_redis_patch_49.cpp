@@ -40,6 +40,14 @@
  */
 #define	MALLOC_PRINTF_BUFSIZE	4096
 
+/* Junk fill patterns. */
+#ifndef JEMALLOC_ALLOC_JUNK
+#  define JEMALLOC_ALLOC_JUNK	((uint8_t)0xa5)
+#endif
+#ifndef JEMALLOC_FREE_JUNK
+#  define JEMALLOC_FREE_JUNK	((uint8_t)0x5a)
+#endif
+
 /*
  * Wrap a cpp argument that contains commas such that it isn't broken up into
  * multiple arguments.
@@ -57,73 +65,21 @@
 #	define JEMALLOC_CC_SILENCE_INIT(v)
 #endif
 
-#define	JEMALLOC_GNUC_PREREQ(major, minor)				\
-    (!defined(__clang__) &&						\
-    (__GNUC__ > (major) || (__GNUC__ == (major) && __GNUC_MINOR__ >= (minor))))
-#ifndef __has_builtin
-#  define __has_builtin(builtin) (0)
-#endif
-#define	JEMALLOC_CLANG_HAS_BUILTIN(builtin)				\
-    (defined(__clang__) && __has_builtin(builtin))
-
 #ifdef __GNUC__
 #	define likely(x)   __builtin_expect(!!(x), 1)
 #	define unlikely(x) __builtin_expect(!!(x), 0)
-#  if JEMALLOC_GNUC_PREREQ(4, 6) ||					\
-      JEMALLOC_CLANG_HAS_BUILTIN(__builtin_unreachable)
-#	define unreachable() __builtin_unreachable()
-#  else
-#	define unreachable()
-#  endif
 #else
 #	define likely(x)   !!(x)
 #	define unlikely(x) !!(x)
-#	define unreachable()
 #endif
 
-/*
- * Define a custom assert() in order to reduce the chances of deadlock during
- * assertion failure.
- */
-#ifndef assert
-#define	assert(e) do {							\
-	if (unlikely(config_debug && !(e))) {				\
-		malloc_printf(						\
-		    "<jemalloc>: %s:%d: Failed assertion: \"%s\"\n",	\
-		    __FILE__, __LINE__, #e);				\
-		abort();						\
-	}								\
-} while (0)
+#if !defined(JEMALLOC_INTERNAL_UNREACHABLE)
+#  error JEMALLOC_INTERNAL_UNREACHABLE should have been defined by configure
 #endif
 
-#ifndef not_reached
-#define	not_reached() do {						\
-	if (config_debug) {						\
-		malloc_printf(						\
-		    "<jemalloc>: %s:%d: Unreachable code reached\n",	\
-		    __FILE__, __LINE__);				\
-		abort();						\
-	}								\
-	unreachable();							\
-} while (0)
-#endif
+#define unreachable() JEMALLOC_INTERNAL_UNREACHABLE()
 
-#ifndef not_implemented
-#define	not_implemented() do {						\
-	if (config_debug) {						\
-		malloc_printf("<jemalloc>: %s:%d: Not implemented\n",	\
-		    __FILE__, __LINE__);				\
-		abort();						\
-	}								\
-} while (0)
-#endif
-
-#ifndef assert_not_implemented
-#define	assert_not_implemented(e) do {					\
-	if (unlikely(config_debug && !(e)))				\
-		not_implemented();					\
-} while (0)
-#endif
+#include "jemalloc/internal/assert.h"
 
 /* Use to assert a particular configuration, e.g., cassert(config_debug). */
 #define	cassert(c) do {							\
@@ -148,9 +104,9 @@ void	malloc_write(const char *s);
  * malloc_vsnprintf() supports a subset of snprintf(3) that avoids floating
  * point math.
  */
-int	malloc_vsnprintf(char *str, size_t size, const char *format,
+size_t	malloc_vsnprintf(char *str, size_t size, const char *format,
     va_list ap);
-int	malloc_snprintf(char *str, size_t size, const char *format, ...)
+size_t	malloc_snprintf(char *str, size_t size, const char *format, ...)
     JEMALLOC_FORMAT_PRINTF(3, 4);
 void	malloc_vcprintf(void (*write_cb)(void *, const char *), void *cbopaque,
     const char *format, va_list ap);
@@ -163,38 +119,91 @@ void	malloc_printf(const char *format, ...) JEMALLOC_FORMAT_PRINTF(1, 2);
 #ifdef JEMALLOC_H_INLINES
 
 #ifndef JEMALLOC_ENABLE_INLINE
-int	jemalloc_ffsl(long bitmap);
-int	jemalloc_ffs(int bitmap);
-size_t	pow2_ceil(size_t x);
-size_t	lg_floor(size_t x);
+unsigned	ffs_llu(unsigned long long bitmap);
+unsigned	ffs_lu(unsigned long bitmap);
+unsigned	ffs_u(unsigned bitmap);
+unsigned	ffs_zu(size_t bitmap);
+unsigned	ffs_u64(uint64_t bitmap);
+unsigned	ffs_u32(uint32_t bitmap);
+uint64_t	pow2_ceil_u64(uint64_t x);
+uint32_t	pow2_ceil_u32(uint32_t x);
+size_t	pow2_ceil_zu(size_t x);
+unsigned	lg_floor(size_t x);
 void	set_errno(int errnum);
 int	get_errno(void);
 #endif
 
 #if (defined(JEMALLOC_ENABLE_INLINE) || defined(JEMALLOC_UTIL_C_))
 
 /* Sanity check. */
-#if !defined(JEMALLOC_INTERNAL_FFSL) || !defined(JEMALLOC_INTERNAL_FFS)
-#  error Both JEMALLOC_INTERNAL_FFSL && JEMALLOC_INTERNAL_FFS should have been defined by configure
+#if !defined(JEMALLOC_INTERNAL_FFSLL) || !defined(JEMALLOC_INTERNAL_FFSL) \
+    || !defined(JEMALLOC_INTERNAL_FFS)
+#  error JEMALLOC_INTERNAL_FFS{,L,LL} should have been defined by configure
 #endif
 
-JEMALLOC_ALWAYS_INLINE int
-jemalloc_ffsl(long bitmap)
+JEMALLOC_ALWAYS_INLINE unsigned
+ffs_llu(unsigned long long bitmap)
+{
+
+	return (JEMALLOC_INTERNAL_FFSLL(bitmap));
+}
+
+JEMALLOC_ALWAYS_INLINE unsigned
+ffs_lu(unsigned long bitmap)
 {
 
 	return (JEMALLOC_INTERNAL_FFSL(bitmap));
 }
 
-JEMALLOC_ALWAYS_INLINE int
-jemalloc_ffs(int bitmap)
+JEMALLOC_ALWAYS_INLINE unsigned
+ffs_u(unsigned bitmap)
 {
 
 	return (JEMALLOC_INTERNAL_FFS(bitmap));
 }
 
-/* Compute the smallest power of 2 that is >= x. */
-JEMALLOC_INLINE size_t
-pow2_ceil(size_t x)
+JEMALLOC_ALWAYS_INLINE unsigned
+ffs_zu(size_t bitmap)
+{
+
+#if LG_SIZEOF_PTR == LG_SIZEOF_INT
+	return (ffs_u(bitmap));
+#elif LG_SIZEOF_PTR == LG_SIZEOF_LONG
+	return (ffs_lu(bitmap));
+#elif LG_SIZEOF_PTR == LG_SIZEOF_LONG_LONG
+	return (ffs_llu(bitmap));
+#else
+#error No implementation for size_t ffs()
+#endif
+}
+
+JEMALLOC_ALWAYS_INLINE unsigned
+ffs_u64(uint64_t bitmap)
+{
+
+#if LG_SIZEOF_LONG == 3
+	return (ffs_lu(bitmap));
+#elif LG_SIZEOF_LONG_LONG == 3
+	return (ffs_llu(bitmap));
+#else
+#error No implementation for 64-bit ffs()
+#endif
+}
+
+JEMALLOC_ALWAYS_INLINE unsigned
+ffs_u32(uint32_t bitmap)
+{
+
+#if LG_SIZEOF_INT == 2
+	return (ffs_u(bitmap));
+#else
+#error No implementation for 32-bit ffs()
+#endif
+	return (ffs_u(bitmap));
+}
+
+JEMALLOC_INLINE uint64_t
+pow2_ceil_u64(uint64_t x)
 {
 
 	x--;
@@ -203,15 +212,39 @@ pow2_ceil(size_t x)
 	x |= x >> 4;
 	x |= x >> 8;
 	x |= x >> 16;
-#if (LG_SIZEOF_PTR == 3)
 	x |= x >> 32;
-#endif
 	x++;
 	return (x);
 }
 
-#if (defined(__i386__) || defined(__amd64__) || defined(__x86_64__))
+JEMALLOC_INLINE uint32_t
+pow2_ceil_u32(uint32_t x)
+{
+
+	x--;
+	x |= x >> 1;
+	x |= x >> 2;
+	x |= x >> 4;
+	x |= x >> 8;
+	x |= x >> 16;
+	x++;
+	return (x);
+}
+
+/* Compute the smallest power of 2 that is >= x. */
 JEMALLOC_INLINE size_t
+pow2_ceil_zu(size_t x)
+{
+
+#if (LG_SIZEOF_PTR == 3)
+	return (pow2_ceil_u64(x));
+#else
+	return (pow2_ceil_u32(x));
+#endif
+}
+
+#if (defined(__i386__) || defined(__amd64__) || defined(__x86_64__))
+JEMALLOC_INLINE unsigned
 lg_floor(size_t x)
 {
 	size_t ret;
@@ -222,10 +255,11 @@ lg_floor(size_t x)
 	    : "=r"(ret) // Outputs.
 	    : "r"(x)    // Inputs.
 	    );
-	return (ret);
+	assert(ret < UINT_MAX);
+	return ((unsigned)ret);
 }
 #elif (defined(_MSC_VER))
-JEMALLOC_INLINE size_t
+JEMALLOC_INLINE unsigned
 lg_floor(size_t x)
 {
 	unsigned long ret;
@@ -237,12 +271,13 @@ lg_floor(size_t x)
 #elif (LG_SIZEOF_PTR == 2)
 	_BitScanReverse(&ret, x);
 #else
-#  error "Unsupported type sizes for lg_floor()"
+#  error "Unsupported type size for lg_floor()"
 #endif
-	return (ret);
+	assert(ret < UINT_MAX);
+	return ((unsigned)ret);
 }
 #elif (defined(JEMALLOC_HAVE_BUILTIN_CLZ))
-JEMALLOC_INLINE size_t
+JEMALLOC_INLINE unsigned
 lg_floor(size_t x)
 {
 
@@ -253,11 +288,11 @@ lg_floor(size_t x)
 #elif (LG_SIZEOF_PTR == LG_SIZEOF_LONG)
 	return (((8 << LG_SIZEOF_PTR) - 1) - __builtin_clzl(x));
 #else
-#  error "Unsupported type sizes for lg_floor()"
+#  error "Unsupported type size for lg_floor()"
 #endif
 }
 #else
-JEMALLOC_INLINE size_t
+JEMALLOC_INLINE unsigned
 lg_floor(size_t x)
 {
 
@@ -268,20 +303,13 @@ lg_floor(size_t x)
 	x |= (x >> 4);
 	x |= (x >> 8);
 	x |= (x >> 16);
-#if (LG_SIZEOF_PTR == 3 && LG_SIZEOF_PTR == LG_SIZEOF_LONG)
+#if (LG_SIZEOF_PTR == 3)
 	x |= (x >> 32);
-	if (x == KZU(0xffffffffffffffff))
-		return (63);
-	x++;
-	return (jemalloc_ffsl(x) - 2);
-#elif (LG_SIZEOF_PTR == 2)
-	if (x == KZU(0xffffffff))
-		return (31);
-	x++;
-	return (jemalloc_ffs(x) - 2);
-#else
-#  error "Unsupported type sizes for lg_floor()"
 #endif
+	if (x == SIZE_T_MAX)
+		return ((8 << LG_SIZEOF_PTR) - 1);
+	x++;
+	return (ffs_zu(x) - 2);
 }
 #endif
 