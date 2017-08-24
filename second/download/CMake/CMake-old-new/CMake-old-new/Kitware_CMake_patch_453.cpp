@@ -124,27 +124,16 @@ extern "C" {
  * easy to compare versions at build time: for version a.b.c, the
  * version number is printf("%d%03d%03d",a,b,c).  For example, if you
  * know your application requires version 2.12.108 or later, you can
- * assert that ARCHIVE_VERSION >= 2012108.
- *
- * This single-number format was introduced with libarchive 1.9.0 in
- * the libarchive 1.x family and libarchive 2.2.4 in the libarchive
- * 2.x family.  The following may be useful if you really want to do
- * feature detection for earlier libarchive versions (which defined
- * ARCHIVE_API_VERSION and ARCHIVE_API_FEATURE instead):
- *
- * #ifndef ARCHIVE_VERSION_NUMBER
- * #define ARCHIVE_VERSION_NUMBER	\
- *             (ARCHIVE_API_VERSION * 1000000 + ARCHIVE_API_FEATURE * 1000)
- * #endif
+ * assert that ARCHIVE_VERSION_NUMBER >= 2012108.
  */
 /* Note: Compiler will complain if this does not match archive_entry.h! */
-#define	ARCHIVE_VERSION_NUMBER 3000001
+#define	ARCHIVE_VERSION_NUMBER 3000002
 __LA_DECL int		archive_version_number(void);
 
 /*
  * Textual name/version of the library, useful for version displays.
  */
-#define	ARCHIVE_VERSION_STRING "libarchive 3.0.1b"
+#define	ARCHIVE_VERSION_STRING "libarchive 3.0.2"
 __LA_DECL const char *	archive_version_string(void);
 
 /* Declare our basic types. */
@@ -447,8 +436,6 @@ __LA_DECL int archive_read_data_block(struct archive *a,
  *  'into_fd': writes data to specified filedes
  */
 __LA_DECL int archive_read_data_skip(struct archive *);
-__LA_DECL int archive_read_data_into_buffer(struct archive *,
-			    void *buffer, __LA_SSIZE_T len);
 __LA_DECL int archive_read_data_into_fd(struct archive *, int fd);
 
 /*