 * header and library are very different, you should expect some

 * strangeness.  Don't do that.

 */

__LA_DECL int		archive_version_number(void);



/*

 * Textual name/version of the library, useful for version displays.

 */

#define	ARCHIVE_VERSION_ONLY_STRING "3.2.0"

#define	ARCHIVE_VERSION_STRING "libarchive " ARCHIVE_VERSION_ONLY_STRING

__LA_DECL const char *	archive_version_string(void);



