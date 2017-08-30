 * easy to compare versions at build time: for version a.b.c, the

 * version number is printf("%d%03d%03d",a,b,c).  For example, if you

 * know your application requires version 2.12.108 or later, you can

 * assert that ARCHIVE_VERSION >= 2012108.

 *

 * This single-number format was introduced with libarchive 1.9.0 in

 * the libarchive 1.x family and libarchive 2.2.4 in the libarchive

 * 2.x family.  The following may be useful if you really want to do

 * feature detection for earlier libarchive versions (which defined

 * ARCHIVE_API_VERSION and ARCHIVE_API_FEATURE instead):

 *

 * #ifndef ARCHIVE_VERSION_NUMBER

 * #define ARCHIVE_VERSION_NUMBER	\

 *             (ARCHIVE_API_VERSION * 1000000 + ARCHIVE_API_FEATURE * 1000)

 * #endif

 */

/* Note: Compiler will complain if this does not match archive_entry.h! */

#define	ARCHIVE_VERSION_NUMBER 3000001

__LA_DECL int		archive_version_number(void);



/*

 * Textual name/version of the library, useful for version displays.

 */

#define	ARCHIVE_VERSION_STRING "libarchive 3.0.1b"

__LA_DECL const char *	archive_version_string(void);



/* Declare our basic types. */

