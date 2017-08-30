 * easy to compare versions at build time: for version a.b.c, the

 * version number is printf("%d%03d%03d",a,b,c).  For example, if you

 * know your application requires version 2.12.108 or later, you can

 * assert that ARCHIVE_VERSION_NUMBER >= 2012108.

 */

/* Note: Compiler will complain if this does not match archive_entry.h! */

#define	ARCHIVE_VERSION_NUMBER 3000002

__LA_DECL int		archive_version_number(void);



/*

 * Textual name/version of the library, useful for version displays.

 */

#define	ARCHIVE_VERSION_STRING "libarchive 3.0.2"

__LA_DECL const char *	archive_version_string(void);



/* Declare our basic types. */

