@@ -63,13 +63,6 @@
 # else
 #  define	__LA_SSIZE_T	long
 # endif
-# if defined(__BORLANDC__)
-#  define	__LA_UID_T	uid_t
-#  define	__LA_GID_T	gid_t
-# else
-#  define	__LA_UID_T	short
-#  define	__LA_GID_T	short
-# endif
 #else
 # include <unistd.h>  /* ssize_t, uid_t, and gid_t */
 # if defined(_SCO_DS) || defined(__osf__)
@@ -78,8 +71,6 @@
 #  define	__LA_INT64_T	int64_t
 # endif
 # define	__LA_SSIZE_T	ssize_t
-# define	__LA_UID_T	uid_t
-# define	__LA_GID_T	gid_t
 #endif
 
 /*
@@ -113,6 +104,12 @@
 #define	__LA_PRINTF(fmtarg, firstvararg)	/* nothing */
 #endif
 
+#if defined(__GNUC__) && __GNUC__ >= 3 && __GNUC_MINOR__ >= 1
+# define __LA_DEPRECATED __attribute__((deprecated))
+#else
+# define __LA_DEPRECATED
+#endif
+
 #ifdef __cplusplus
 extern "C" {
 #endif
@@ -134,13 +131,13 @@ extern "C" {
  * assert that ARCHIVE_VERSION_NUMBER >= 2012108.
  */
 /* Note: Compiler will complain if this does not match archive_entry.h! */
-#define	ARCHIVE_VERSION_NUMBER 3000002
+#define	ARCHIVE_VERSION_NUMBER 3001002
 __LA_DECL int		archive_version_number(void);
 
 /*
  * Textual name/version of the library, useful for version displays.
  */
-#define	ARCHIVE_VERSION_STRING "libarchive 3.0.2"
+#define	ARCHIVE_VERSION_STRING "libarchive 3.1.2"
 __LA_DECL const char *	archive_version_string(void);
 
 /* Declare our basic types. */
@@ -210,6 +207,13 @@ typedef int	archive_open_callback(struct archive *, void *_client_data);
 
 typedef int	archive_close_callback(struct archive *, void *_client_data);
 
+/* Switches from one client data object to the next/prev client data object.
+ * This is useful for reading from different data blocks such as a set of files
+ * that make up one large file.
+ */
+typedef int archive_switch_callback(struct archive *, void *_client_data1,
+			    void *_client_data2);
+
 /*
  * Codes to identify various stream filters.
  */
@@ -223,6 +227,9 @@ typedef int	archive_close_callback(struct archive *, void *_client_data);
 #define	ARCHIVE_FILTER_UU	7
 #define	ARCHIVE_FILTER_RPM	8
 #define	ARCHIVE_FILTER_LZIP	9
+#define	ARCHIVE_FILTER_LRZIP	10
+#define	ARCHIVE_FILTER_LZOP	11
+#define	ARCHIVE_FILTER_GRZIP	12
 
 #if ARCHIVE_VERSION_NUMBER < 4000000
 #define	ARCHIVE_COMPRESSION_NONE	ARCHIVE_FILTER_NONE
@@ -235,6 +242,7 @@ typedef int	archive_close_callback(struct archive *, void *_client_data);
 #define	ARCHIVE_COMPRESSION_UU		ARCHIVE_FILTER_UU
 #define	ARCHIVE_COMPRESSION_RPM		ARCHIVE_FILTER_RPM
 #define	ARCHIVE_COMPRESSION_LZIP	ARCHIVE_FILTER_LZIP
+#define	ARCHIVE_COMPRESSION_LRZIP	ARCHIVE_FILTER_LRZIP
 #endif
 
 /*
@@ -307,37 +315,49 @@ __LA_DECL struct archive	*archive_read_new(void);
  */
 
 #if ARCHIVE_VERSION_NUMBER < 4000000
-__LA_DECL int archive_read_support_compression_all(struct archive *);
-__LA_DECL int archive_read_support_compression_bzip2(struct archive *);
-__LA_DECL int archive_read_support_compression_compress(struct archive *);
-__LA_DECL int archive_read_support_compression_gzip(struct archive *);
-__LA_DECL int archive_read_support_compression_lzip(struct archive *);
-__LA_DECL int archive_read_support_compression_lzma(struct archive *);
-__LA_DECL int archive_read_support_compression_none(struct archive *);
+__LA_DECL int archive_read_support_compression_all(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_bzip2(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_compress(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_gzip(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_lzip(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_lzma(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_none(struct archive *)
+		__LA_DEPRECATED;
 __LA_DECL int archive_read_support_compression_program(struct archive *,
-		     const char *command);
+		     const char *command) __LA_DEPRECATED;
 __LA_DECL int archive_read_support_compression_program_signature
 		(struct archive *, const char *,
-				    const void * /* match */, size_t);
-
-__LA_DECL int archive_read_support_compression_rpm(struct archive *);
-__LA_DECL int archive_read_support_compression_uu(struct archive *);
-__LA_DECL int archive_read_support_compression_xz(struct archive *);
+		 const void * /* match */, size_t) __LA_DEPRECATED;
+
+__LA_DECL int archive_read_support_compression_rpm(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_uu(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_read_support_compression_xz(struct archive *)
+		__LA_DEPRECATED;
 #endif
 
 __LA_DECL int archive_read_support_filter_all(struct archive *);
 __LA_DECL int archive_read_support_filter_bzip2(struct archive *);
 __LA_DECL int archive_read_support_filter_compress(struct archive *);
 __LA_DECL int archive_read_support_filter_gzip(struct archive *);
+__LA_DECL int archive_read_support_filter_grzip(struct archive *);
+__LA_DECL int archive_read_support_filter_lrzip(struct archive *);
 __LA_DECL int archive_read_support_filter_lzip(struct archive *);
 __LA_DECL int archive_read_support_filter_lzma(struct archive *);
+__LA_DECL int archive_read_support_filter_lzop(struct archive *);
 __LA_DECL int archive_read_support_filter_none(struct archive *);
 __LA_DECL int archive_read_support_filter_program(struct archive *,
 		     const char *command);
 __LA_DECL int archive_read_support_filter_program_signature
-		(struct archive *, const char *,
+		(struct archive *, const char * /* cmd */,
 				    const void * /* match */, size_t);
-
 __LA_DECL int archive_read_support_filter_rpm(struct archive *);
 __LA_DECL int archive_read_support_filter_uu(struct archive *);
 __LA_DECL int archive_read_support_filter_xz(struct archive *);
@@ -359,6 +379,17 @@ __LA_DECL int archive_read_support_format_tar(struct archive *);
 __LA_DECL int archive_read_support_format_xar(struct archive *);
 __LA_DECL int archive_read_support_format_zip(struct archive *);
 
+/* Functions to manually set the format and filters to be used. This is
+ * useful to bypass the bidding process when the format and filters to use
+ * is known in advance.
+ */
+__LA_DECL int archive_read_set_format(struct archive *, int);
+__LA_DECL int archive_read_append_filter(struct archive *, int);
+__LA_DECL int archive_read_append_filter_program(struct archive *,
+    const char *);
+__LA_DECL int archive_read_append_filter_program_signature
+    (struct archive *, const char *, const void * /* match */, size_t);
+
 /* Set various callbacks. */
 __LA_DECL int archive_read_set_open_callback(struct archive *,
     archive_open_callback *);
@@ -370,8 +401,23 @@ __LA_DECL int archive_read_set_skip_callback(struct archive *,
     archive_skip_callback *);
 __LA_DECL int archive_read_set_close_callback(struct archive *,
     archive_close_callback *);
-/* The callback data is provided to all of the callbacks above. */
+/* Callback used to switch between one data object to the next */
+__LA_DECL int archive_read_set_switch_callback(struct archive *,
+    archive_switch_callback *);
+
+/* This sets the first data object. */
 __LA_DECL int archive_read_set_callback_data(struct archive *, void *);
+/* This sets data object at specified index */
+__LA_DECL int archive_read_set_callback_data2(struct archive *, void *,
+    unsigned int);
+/* This adds a data object at the specified index. */
+__LA_DECL int archive_read_add_callback_data(struct archive *, void *,
+    unsigned int);
+/* This appends a data object to the end of list */
+__LA_DECL int archive_read_append_callback_data(struct archive *, void *);
+/* This prepends a data object to the beginning of list */
+__LA_DECL int archive_read_prepend_callback_data(struct archive *, void *);
+
 /* Opening freezes the callbacks. */
 __LA_DECL int archive_read_open1(struct archive *);
 
@@ -391,11 +437,15 @@ __LA_DECL int archive_read_open2(struct archive *, void *_client_data,
 /* Use this if you know the filename.  Note: NULL indicates stdin. */
 __LA_DECL int archive_read_open_filename(struct archive *,
 		     const char *_filename, size_t _block_size);
+/* Use this for reading multivolume files by filenames.
+ * NOTE: Must be NULL terminated. Sorting is NOT done. */
+__LA_DECL int archive_read_open_filenames(struct archive *,
+		     const char **_filenames, size_t _block_size);
 __LA_DECL int archive_read_open_filename_w(struct archive *,
 		     const wchar_t *_filename, size_t _block_size);
 /* archive_read_open_file() is a deprecated synonym for ..._open_filename(). */
 __LA_DECL int archive_read_open_file(struct archive *,
-		     const char *_filename, size_t _block_size);
+		     const char *_filename, size_t _block_size) __LA_DEPRECATED;
 /* Read an archive that's stored in memory. */
 __LA_DECL int archive_read_open_memory(struct archive *,
 		     void * buff, size_t size);
@@ -427,6 +477,9 @@ __LA_DECL __LA_INT64_T		 archive_read_header_position(struct archive *);
 __LA_DECL __LA_SSIZE_T		 archive_read_data(struct archive *,
 				    void *, size_t);
 
+/* Seek within the body of an entry.  Similar to lseek(2). */
+__LA_DECL __LA_INT64_T archive_seek_data(struct archive *, __LA_INT64_T, int);
+
 /*
  * A zero-copy version of archive_read_data that also exposes the file offset
  * of each returned block.  Note that the client has no way to specify
@@ -510,6 +563,12 @@ __LA_DECL int archive_read_set_options(struct archive *_a,
 /* Default: Do not restore Mac extended metadata. */
 /* This has no effect except on Mac OS. */
 #define	ARCHIVE_EXTRACT_MAC_METADATA		(0x2000)
+/* Default: Use HFS+ compression if it was compressed. */
+/* This has no effect except on Mac OS v10.6 or later. */
+#define	ARCHIVE_EXTRACT_NO_HFS_COMPRESSION	(0x4000)
+/* Default: Do not use HFS+ compression if it was not compressed. */
+/* This has no effect except on Mac OS v10.6 or later. */
+#define	ARCHIVE_EXTRACT_HFS_COMPRESSION_FORCED	(0x8000)
 
 __LA_DECL int archive_read_extract(struct archive *, struct archive_entry *,
 		     int flags);
@@ -530,7 +589,7 @@ __LA_DECL int		 archive_read_close(struct archive *);
 __LA_DECL int		 archive_read_free(struct archive *);
 #if ARCHIVE_VERSION_NUMBER < 4000000
 /* Synonym for archive_read_free() for backwards compatibility. */
-__LA_DECL int		 archive_read_finish(struct archive *);
+__LA_DECL int		 archive_read_finish(struct archive *) __LA_DEPRECATED;
 #endif
 
 /*-
@@ -563,25 +622,41 @@ __LA_DECL int archive_write_set_skip_file(struct archive *,
     __LA_INT64_T, __LA_INT64_T);
 
 #if ARCHIVE_VERSION_NUMBER < 4000000
-__LA_DECL int archive_write_set_compression_bzip2(struct archive *);
-__LA_DECL int archive_write_set_compression_compress(struct archive *);
-__LA_DECL int archive_write_set_compression_gzip(struct archive *);
-__LA_DECL int archive_write_set_compression_lzip(struct archive *);
-__LA_DECL int archive_write_set_compression_lzma(struct archive *);
-__LA_DECL int archive_write_set_compression_none(struct archive *);
+__LA_DECL int archive_write_set_compression_bzip2(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_write_set_compression_compress(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_write_set_compression_gzip(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_write_set_compression_lzip(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_write_set_compression_lzma(struct archive *)
+		__LA_DEPRECATED;
+__LA_DECL int archive_write_set_compression_none(struct archive *)
+		__LA_DEPRECATED;
 __LA_DECL int archive_write_set_compression_program(struct archive *,
-		     const char *cmd);
-__LA_DECL int archive_write_set_compression_xz(struct archive *);
+		     const char *cmd) __LA_DEPRECATED;
+__LA_DECL int archive_write_set_compression_xz(struct archive *)
+		__LA_DEPRECATED;
 #endif
 
+/* A convenience function to set the filter based on the code. */
+__LA_DECL int archive_write_add_filter(struct archive *, int filter_code);
+__LA_DECL int archive_write_add_filter_by_name(struct archive *,
+		     const char *name);
+__LA_DECL int archive_write_add_filter_b64encode(struct archive *);
 __LA_DECL int archive_write_add_filter_bzip2(struct archive *);
 __LA_DECL int archive_write_add_filter_compress(struct archive *);
+__LA_DECL int archive_write_add_filter_grzip(struct archive *);
 __LA_DECL int archive_write_add_filter_gzip(struct archive *);
+__LA_DECL int archive_write_add_filter_lrzip(struct archive *);
 __LA_DECL int archive_write_add_filter_lzip(struct archive *);
 __LA_DECL int archive_write_add_filter_lzma(struct archive *);
+__LA_DECL int archive_write_add_filter_lzop(struct archive *);
 __LA_DECL int archive_write_add_filter_none(struct archive *);
 __LA_DECL int archive_write_add_filter_program(struct archive *,
 		     const char *cmd);
+__LA_DECL int archive_write_add_filter_uuencode(struct archive *);
 __LA_DECL int archive_write_add_filter_xz(struct archive *);
 
 
@@ -598,14 +673,18 @@ __LA_DECL int archive_write_set_format_cpio_newc(struct archive *);
 __LA_DECL int archive_write_set_format_gnutar(struct archive *);
 __LA_DECL int archive_write_set_format_iso9660(struct archive *);
 __LA_DECL int archive_write_set_format_mtree(struct archive *);
+__LA_DECL int archive_write_set_format_mtree_classic(struct archive *);
 /* TODO: int archive_write_set_format_old_tar(struct archive *); */
 __LA_DECL int archive_write_set_format_pax(struct archive *);
 __LA_DECL int archive_write_set_format_pax_restricted(struct archive *);
 __LA_DECL int archive_write_set_format_shar(struct archive *);
 __LA_DECL int archive_write_set_format_shar_dump(struct archive *);
 __LA_DECL int archive_write_set_format_ustar(struct archive *);
+__LA_DECL int archive_write_set_format_v7tar(struct archive *);
 __LA_DECL int archive_write_set_format_xar(struct archive *);
 __LA_DECL int archive_write_set_format_zip(struct archive *);
+__LA_DECL int archive_write_zip_set_compression_deflate(struct archive *);
+__LA_DECL int archive_write_zip_set_compression_store(struct archive *);
 __LA_DECL int archive_write_open(struct archive *, void *,
 		     archive_open_callback *, archive_write_callback *,
 		     archive_close_callback *);
@@ -614,7 +693,8 @@ __LA_DECL int archive_write_open_filename(struct archive *, const char *_file);
 __LA_DECL int archive_write_open_filename_w(struct archive *,
 		     const wchar_t *_file);
 /* A deprecated synonym for archive_write_open_filename() */
-__LA_DECL int archive_write_open_file(struct archive *, const char *_file);
+__LA_DECL int archive_write_open_file(struct archive *, const char *_file)
+		__LA_DEPRECATED;
 __LA_DECL int archive_write_open_FILE(struct archive *, FILE *);
 /* _buffSize is the size of the buffer, _used refers to a variable that
  * will be updated after each write into the buffer. */
@@ -636,12 +716,16 @@ __LA_DECL __LA_SSIZE_T	 archive_write_data_block(struct archive *,
 
 __LA_DECL int		 archive_write_finish_entry(struct archive *);
 __LA_DECL int		 archive_write_close(struct archive *);
+/* Marks the archive as FATAL so that a subsequent free() operation
+ * won't try to close() cleanly.  Provides a fast abort capability
+ * when the client discovers that things have gone wrong. */
+__LA_DECL int            archive_write_fail(struct archive *);
 /* This can fail if the archive wasn't already closed, in which case
  * archive_write_free() will implicitly call archive_write_close(). */
 __LA_DECL int		 archive_write_free(struct archive *);
 #if ARCHIVE_VERSION_NUMBER < 4000000
 /* Synonym for archive_write_free() for backwards compatibility. */
-__LA_DECL int		 archive_write_finish(struct archive *);
+__LA_DECL int		 archive_write_finish(struct archive *) __LA_DEPRECATED;
 #endif
 
 /*
@@ -765,11 +849,42 @@ __LA_DECL int	archive_read_disk_open_w(struct archive *, const wchar_t *);
  * traversal.
  */
 __LA_DECL int	archive_read_disk_descend(struct archive *);
+__LA_DECL int	archive_read_disk_can_descend(struct archive *);
 __LA_DECL int	archive_read_disk_current_filesystem(struct archive *);
 __LA_DECL int	archive_read_disk_current_filesystem_is_synthetic(struct archive *);
 __LA_DECL int	archive_read_disk_current_filesystem_is_remote(struct archive *);
 /* Request that the access time of the entry visited by travesal be restored. */
 __LA_DECL int  archive_read_disk_set_atime_restored(struct archive *);
+/*
+ * Set behavior. The "flags" argument selects optional behavior.
+ */
+/* Request that the access time of the entry visited by travesal be restored.
+ * This is the same as archive_read_disk_set_atime_restored. */
+#define	ARCHIVE_READDISK_RESTORE_ATIME		(0x0001)
+/* Default: Do not skip an entry which has nodump flags. */
+#define	ARCHIVE_READDISK_HONOR_NODUMP		(0x0002)
+/* Default: Skip a mac resource fork file whose prefix is "._" because of
+ * using copyfile. */
+#define	ARCHIVE_READDISK_MAC_COPYFILE		(0x0004)
+/* Default: Do not traverse mount points. */
+#define	ARCHIVE_READDISK_NO_TRAVERSE_MOUNTS	(0x0008)
+
+__LA_DECL int  archive_read_disk_set_behavior(struct archive *,
+		    int flags);
+
+/*
+ * Set archive_match object that will be used in archive_read_disk to
+ * know whether an entry should be skipped. The callback function
+ * _excluded_func will be invoked when an entry is skipped by the result
+ * of archive_match.
+ */
+__LA_DECL int	archive_read_disk_set_matching(struct archive *,
+		    struct archive *_matching, void (*_excluded_func)
+		    (struct archive *, void *, struct archive_entry *),
+		    void *_client_data);
+__LA_DECL int	archive_read_disk_set_metadata_filter_callback(struct archive *,
+		    int (*_metadata_filter_func)(struct archive *, void *,
+		    	struct archive_entry *), void *_client_data);
 
 /*
  * Accessor functions to read/set various information in
@@ -789,13 +904,17 @@ __LA_DECL const char *	 archive_filter_name(struct archive *, int);
 /* These don't properly handle multiple filters, so are deprecated and
  * will eventually be removed. */
 /* As of libarchive 3.0, this is an alias for archive_filter_bytes(a, -1); */
-__LA_DECL __LA_INT64_T	 archive_position_compressed(struct archive *);
+__LA_DECL __LA_INT64_T	 archive_position_compressed(struct archive *)
+				__LA_DEPRECATED;
 /* As of libarchive 3.0, this is an alias for archive_filter_bytes(a, 0); */
-__LA_DECL __LA_INT64_T	 archive_position_uncompressed(struct archive *);
+__LA_DECL __LA_INT64_T	 archive_position_uncompressed(struct archive *)
+				__LA_DEPRECATED;
 /* As of libarchive 3.0, this is an alias for archive_filter_name(a, 0); */
-__LA_DECL const char	*archive_compression_name(struct archive *);
+__LA_DECL const char	*archive_compression_name(struct archive *)
+				__LA_DEPRECATED;
 /* As of libarchive 3.0, this is an alias for archive_filter_code(a, 0); */
-__LA_DECL int		 archive_compression(struct archive *);
+__LA_DECL int		 archive_compression(struct archive *)
+				__LA_DEPRECATED;
 #endif
 
 __LA_DECL int		 archive_errno(struct archive *);
@@ -809,14 +928,116 @@ __LA_DECL void		 archive_copy_error(struct archive *dest,
 			    struct archive *src);
 __LA_DECL int		 archive_file_count(struct archive *);
 
+/*
+ * ARCHIVE_MATCH API
+ */
+__LA_DECL struct archive *archive_match_new(void);
+__LA_DECL int	archive_match_free(struct archive *);
+
+/*
+ * Test if archive_entry is excluded.
+ * This is a convenience function. This is the same as calling all
+ * archive_match_path_excluded, archive_match_time_excluded
+ * and archive_match_owner_excluded.
+ */
+__LA_DECL int	archive_match_excluded(struct archive *,
+		    struct archive_entry *);
+
+/*
+ * Test if pathname is excluded. The conditions are set by following functions.
+ */
+__LA_DECL int	archive_match_path_excluded(struct archive *,
+		    struct archive_entry *);
+/* Add exclusion pathname pattern. */
+__LA_DECL int	archive_match_exclude_pattern(struct archive *, const char *);
+__LA_DECL int	archive_match_exclude_pattern_w(struct archive *,
+		    const wchar_t *);
+/* Add exclusion pathname pattern from file. */
+__LA_DECL int	archive_match_exclude_pattern_from_file(struct archive *,
+		    const char *, int _nullSeparator);
+__LA_DECL int	archive_match_exclude_pattern_from_file_w(struct archive *,
+		    const wchar_t *, int _nullSeparator);
+/* Add inclusion pathname pattern. */
+__LA_DECL int	archive_match_include_pattern(struct archive *, const char *);
+__LA_DECL int	archive_match_include_pattern_w(struct archive *,
+		    const wchar_t *);
+/* Add inclusion pathname pattern from file. */
+__LA_DECL int	archive_match_include_pattern_from_file(struct archive *,
+		    const char *, int _nullSeparator);
+__LA_DECL int	archive_match_include_pattern_from_file_w(struct archive *,
+		    const wchar_t *, int _nullSeparator);
+/*
+ * How to get statistic information for inclusion patterns.
+ */
+/* Return the amount number of unmatched inclusion patterns. */
+__LA_DECL int	archive_match_path_unmatched_inclusions(struct archive *);
+/* Return the pattern of unmatched inclusion with ARCHIVE_OK.
+ * Return ARCHIVE_EOF if there is no inclusion pattern. */
+__LA_DECL int	archive_match_path_unmatched_inclusions_next(
+		    struct archive *, const char **);
+__LA_DECL int	archive_match_path_unmatched_inclusions_next_w(
+		    struct archive *, const wchar_t **);
+
+/*
+ * Test if a file is excluded by its time stamp.
+ * The conditions are set by following functions.
+ */
+__LA_DECL int	archive_match_time_excluded(struct archive *,
+		    struct archive_entry *);
+
+/*
+ * Flags to tell a matching type of time stamps. These are used for
+ * following functinos.
+ */
+/* Time flag: mtime to be tested. */
+#define ARCHIVE_MATCH_MTIME	(0x0100)
+/* Time flag: ctime to be tested. */
+#define ARCHIVE_MATCH_CTIME	(0x0200)
+/* Comparison flag: Match the time if it is newer than. */
+#define ARCHIVE_MATCH_NEWER	(0x0001)
+/* Comparison flag: Match the time if it is older than. */
+#define ARCHIVE_MATCH_OLDER	(0x0002)
+/* Comparison flag: Match the time if it is equal to. */
+#define ARCHIVE_MATCH_EQUAL	(0x0010)
+/* Set inclusion time. */
+__LA_DECL int	archive_match_include_time(struct archive *, int _flag,
+		    time_t _sec, long _nsec);
+/* Set inclusion time by a date string. */
+__LA_DECL int	archive_match_include_date(struct archive *, int _flag,
+		    const char *_datestr);
+__LA_DECL int	archive_match_include_date_w(struct archive *, int _flag,
+		    const wchar_t *_datestr);
+/* Set inclusion time by a particluar file. */
+__LA_DECL int	archive_match_include_file_time(struct archive *,
+		    int _flag, const char *_pathname);
+__LA_DECL int	archive_match_include_file_time_w(struct archive *,
+		    int _flag, const wchar_t *_pathname);
+/* Add exclusion entry. */
+__LA_DECL int	archive_match_exclude_entry(struct archive *,
+		    int _flag, struct archive_entry *);
+
+/*
+ * Test if a file is excluded by its uid ,gid, uname or gname.
+ * The conditions are set by following functions.
+ */
+__LA_DECL int	archive_match_owner_excluded(struct archive *,
+		    struct archive_entry *);
+/* Add inclusion uid, gid, uname and gname. */
+__LA_DECL int	archive_match_include_uid(struct archive *, __LA_INT64_T);
+__LA_DECL int	archive_match_include_gid(struct archive *, __LA_INT64_T);
+__LA_DECL int	archive_match_include_uname(struct archive *, const char *);
+__LA_DECL int	archive_match_include_uname_w(struct archive *,
+		    const wchar_t *);
+__LA_DECL int	archive_match_include_gname(struct archive *, const char *);
+__LA_DECL int	archive_match_include_gname_w(struct archive *,
+		    const wchar_t *);
+
 #ifdef __cplusplus
 }
 #endif
 
 /* These are meaningless outside of this header. */
 #undef __LA_DECL
-#undef __LA_GID_T
-#undef __LA_UID_T
 
 /* These need to remain defined because they're used in the
  * callback type definitions.  XXX Fix this.  This is ugly. XXX */