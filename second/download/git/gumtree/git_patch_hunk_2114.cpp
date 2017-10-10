 
 /*
  * Limit size of IO chunks, because huge chunks only cause pain.  OS X
  * 64-bit is buggy, returning EINVAL if len >= INT_MAX; and even in
  * the absence of bugs, large chunks can result in bad latencies when
  * you decide to kill the process.
+ *
+ * We pick 8 MiB as our default, but if the platform defines SSIZE_MAX
+ * that is smaller than that, clip it to SSIZE_MAX, as a call to
+ * read(2) or write(2) larger than that is allowed to fail.  As the last
+ * resort, we allow a port to pass via CFLAGS e.g. "-DMAX_IO_SIZE=value"
+ * to override this, if the definition of SSIZE_MAX given by the platform
+ * is broken.
  */
-#define MAX_IO_SIZE (8*1024*1024)
+#ifndef MAX_IO_SIZE
+# define MAX_IO_SIZE_DEFAULT (8*1024*1024)
+# if defined(SSIZE_MAX) && (SSIZE_MAX < MAX_IO_SIZE_DEFAULT)
+#  define MAX_IO_SIZE SSIZE_MAX
+# else
+#  define MAX_IO_SIZE MAX_IO_SIZE_DEFAULT
+# endif
+#endif
 
 /*
  * xread() is the same a read(), but it automatically restarts read()
  * operations with a recoverable error (EAGAIN and EINTR). xread()
  * DOES NOT GUARANTEE that "len" bytes is read even if the data is available.
  */
