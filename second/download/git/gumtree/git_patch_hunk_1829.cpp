 #define va_copy(dst, src) __va_copy(dst, src)
 #else
 #define va_copy(dst, src) ((dst) = (src))
 #endif
 #endif
 
-#if defined(__GNUC__) || (_MSC_VER >= 1400)
+#if defined(__GNUC__) || (_MSC_VER >= 1400) || defined(__C99_MACRO_WITH_VA_ARGS)
 #define HAVE_VARIADIC_MACROS 1
 #endif
 
 /*
  * Preserves errno, prints a message, but gives no warning for ENOENT.
- * Always returns the return value of unlink(2).
+ * Returns 0 on success, which includes trying to unlink an object that does
+ * not exist.
  */
 int unlink_or_warn(const char *path);
+ /*
+  * Tries to unlink file.  Returns 0 if unlink succeeded
+  * or the file already didn't exist.  Returns -1 and
+  * appends a message to err suitable for
+  * 'error("%s", err->buf)' on error.
+  */
+int unlink_or_msg(const char *file, struct strbuf *err);
 /*
- * Likewise for rmdir(2).
+ * Preserves errno, prints a message, but gives no warning for ENOENT.
+ * Returns 0 on success, which includes trying to remove a directory that does
+ * not exist.
  */
 int rmdir_or_warn(const char *path);
 /*
  * Calls the correct function out of {unlink,rmdir}_or_warn based on
  * the supplied file mode.
  */
