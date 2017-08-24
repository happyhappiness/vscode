@@ -28,9 +28,20 @@
 #ifndef ARCHIVE_H_INCLUDED
 #define	ARCHIVE_H_INCLUDED
 
+/*
+ * The version number is expressed as a single integer that makes it
+ * easy to compare versions at build time: for version a.b.c, the
+ * version number is printf("%d%03d%03d",a,b,c).  For example, if you
+ * know your application requires version 2.12.108 or later, you can
+ * assert that ARCHIVE_VERSION_NUMBER >= 2012108.
+ */
+/* Note: Compiler will complain if this does not match archive_entry.h! */
+#define	ARCHIVE_VERSION_NUMBER 3002000
+
 #include <sys/stat.h>
 #include <stddef.h>  /* for wchar_t */
 #include <stdio.h> /* For FILE * */
+#include <time.h> /* For time_t */
 
 /*
  * Note: archive.h is for use outside of libarchive; the configuration
@@ -41,7 +52,7 @@
  */
 #if defined(__BORLANDC__) && __BORLANDC__ >= 0x560
 # include <stdint.h>
-#elif !defined(__WATCOMC__) && !defined(_MSC_VER) && !defined(__INTERIX) && !defined(__BORLANDC__) && !defined(_SCO_DS)
+#elif !defined(__WATCOMC__) && !defined(_MSC_VER) && !defined(__INTERIX) && !defined(__BORLANDC__) && !defined(_SCO_DS) && !defined(__osf__)
 # include <inttypes.h>
 #endif
 
@@ -56,7 +67,7 @@
 typedef __int64 la_int64_t;
 # else
 # include <unistd.h>  /* ssize_t */
-#  if defined(_SCO_DS)
+#  if defined(_SCO_DS) || defined(__osf__)
 typedef long long la_int64_t;
 #  else
 typedef int64_t la_int64_t;
@@ -85,6 +96,11 @@ typedef ssize_t la_ssize_t;
 # endif
 #endif
 
+/* Large file support for Android */
+#ifdef __ANDROID__
+#include "android_lf.h"
+#endif
+
 /*
  * On Windows, define LIBARCHIVE_STATIC if you're building or using a
  * .lib.  The default here assumes you're building a DLL.  Only
@@ -134,22 +150,12 @@ extern "C" {
  * header and library are very different, you should expect some
  * strangeness.  Don't do that.
  */
-
-/*
- * The version number is expressed as a single integer that makes it
- * easy to compare versions at build time: for version a.b.c, the
- * version number is printf("%d%03d%03d",a,b,c).  For example, if you
- * know your application requires version 2.12.108 or later, you can
- * assert that ARCHIVE_VERSION_NUMBER >= 2012108.
- */
-/* Note: Compiler will complain if this does not match archive_entry.h! */
-#define	ARCHIVE_VERSION_NUMBER 3001002
 __LA_DECL int		archive_version_number(void);
 
 /*
  * Textual name/version of the library, useful for version displays.
  */
-#define	ARCHIVE_VERSION_ONLY_STRING "3.1.2"
+#define	ARCHIVE_VERSION_ONLY_STRING "3.2.0"
 #define	ARCHIVE_VERSION_STRING "libarchive " ARCHIVE_VERSION_ONLY_STRING
 __LA_DECL const char *	archive_version_string(void);
 
@@ -162,6 +168,16 @@ __LA_DECL const char *	archive_version_string(void);
  */
 __LA_DECL const char *	archive_version_details(void);
 
+/*
+ * Returns NULL if libarchive was compiled without the associated library.
+ * Otherwise, returns the version number that libarchive was compiled
+ * against.
+ */
+__LA_DECL const char *  archive_zlib_version(void);
+__LA_DECL const char *  archive_liblzma_version(void);
+__LA_DECL const char *  archive_bzlib_version(void);
+__LA_DECL const char *  archive_liblz4_version(void);
+
 /* Declare our basic types. */
 struct archive;
 struct archive_entry;