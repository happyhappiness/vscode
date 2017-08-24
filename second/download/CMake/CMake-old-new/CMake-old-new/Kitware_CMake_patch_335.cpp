@@ -29,24 +29,6 @@
  * Development supported by Google Summer of Code 2008.
  */
 
-/*
- * The current implementation is very limited:
- *
- *   - No encryption support.
- *   - No ZIP64 support.
- *   - No support for splitting and spanning.
- *   - Only supports regular file and folder entries.
- *
- * Note that generally data in ZIP files is little-endian encoded,
- * with some exceptions.
- *
- * TODO: Since Libarchive is generally 64bit oriented, but this implementation
- * does not yet support sizes exceeding 32bit, it is highly fragile for
- * big archives. This should change when ZIP64 is finally implemented, otherwise
- * some serious checking has to be done.
- *
- */
-
 #include "archive_platform.h"
 __FBSDID("$FreeBSD: head/lib/libarchive/archive_write_set_format_zip.c 201168 2009-12-29 06:15:32Z kientzle $");
 
@@ -77,25 +59,80 @@ __FBSDID("$FreeBSD: head/lib/libarchive/archive_write_set_format_zip.c 201168 20
 #include "archive_crc32.h"
 #endif
 
-#define ZIP_SIGNATURE_LOCAL_FILE_HEADER 0x04034b50
-#define ZIP_SIGNATURE_DATA_DESCRIPTOR 0x08074b50
-#define ZIP_SIGNATURE_FILE_HEADER 0x02014b50
-#define ZIP_SIGNATURE_CENTRAL_DIRECTORY_END 0x06054b50
-#define ZIP_SIGNATURE_EXTRA_TIMESTAMP 0x5455
-#define ZIP_SIGNATURE_EXTRA_NEW_UNIX 0x7875
-#define ZIP_VERSION_EXTRACT 0x0014 /* ZIP version 2.0 is needed. */
-#define ZIP_VERSION_BY 0x0314 /* Made by UNIX, using ZIP version 2.0. */
-#define ZIP_FLAGS 0x08 /* Flagging bit 3 (count from 0) for using data descriptor. */
-#define ZIP_FLAGS_UTF8_NAME	(1 << 11)
+#define ZIP_ENTRY_FLAG_LENGTH_AT_END	(1<<3)
+#define ZIP_ENTRY_FLAG_UTF8_NAME	(1 << 11)
+
 
 enum compression {
-	COMPRESSION_STORE = 0
-#ifdef HAVE_ZLIB_H
-	,
+	COMPRESSION_UNSPECIFIED = -1,
+	COMPRESSION_STORE = 0,
 	COMPRESSION_DEFLATE = 8
+};
+
+#ifdef HAVE_ZLIB_H
+#define COMPRESSION_DEFAULT	COMPRESSION_DEFLATE
+#else
+#define COMPRESSION_DEFAULT	COMPRESSION_STORE
+#endif
+
+struct cd_segment {
+	struct cd_segment *next;
+	size_t buff_size;
+	unsigned char *buff;
+	unsigned char *p;
+};
+
+/* Bits used to enable/disable certain experimental features. */
+#define	EXPERIMENT_LA 1
+#define	EXPERIMENTS_ALL 0xffff
+
+struct zip {
+
+	int64_t entry_offset;
+	int64_t entry_compressed_size;
+	int64_t entry_uncompressed_size;
+	int64_t entry_compressed_written;
+	int64_t entry_uncompressed_written;
+	int64_t entry_uncompressed_limit;
+	struct archive_entry *entry;
+	uint32_t entry_crc32;
+	enum compression entry_compression;
+	int entry_flags;
+	int entry_uses_zip64;
+	int experiments;
+
+	unsigned char *file_header;
+	size_t file_header_extra_offset;
+	unsigned long (*crc32func)(unsigned long crc, const void *buff, size_t len);
+
+	struct cd_segment *central_directory;
+	struct cd_segment *central_directory_last;
+	size_t central_directory_bytes;
+	size_t central_directory_entries;
+
+	int64_t written_bytes; /* Overall position in file. */
+
+	struct archive_string_conv *opt_sconv;
+	struct archive_string_conv *sconv_default;
+	enum compression requested_compression;
+	int init_default_conversion;
+
+#define ZIP_FLAG_AVOID_ZIP64 1
+#define ZIP_FLAG_FORCE_ZIP64 2
+#define ZIP_FLAG_EXPERIMENT_EL 4
+	int flags;
+
+#ifdef HAVE_ZLIB_H
+	z_stream stream;
+	size_t len_buf;
+	unsigned char *buf;
 #endif
 };
 
+/* Don't call this min or MIN, since those are already defined
+   on lots of platforms (but not all). */
+#define zipmin(a, b) ((a) > (b) ? (b) : (a))
+
 static ssize_t archive_write_zip_data(struct archive_write *,
 		   const void *buff, size_t s);
 static int archive_write_zip_close(struct archive_write *);
@@ -108,106 +145,58 @@ static int archive_write_zip_options(struct archive_write *,
 static unsigned int dos_time(const time_t);
 static size_t path_length(struct archive_entry *);
 static int write_path(struct archive_entry *, struct archive_write *);
+static void copy_path(struct archive_entry *, unsigned char *);
+static struct archive_string_conv *get_sconv(struct archive_write *, struct zip *);
 
-#define LOCAL_FILE_HEADER_SIGNATURE		0
-#define LOCAL_FILE_HEADER_VERSION		4
-#define LOCAL_FILE_HEADER_FLAGS			6
-#define LOCAL_FILE_HEADER_COMPRESSION		8
-#define LOCAL_FILE_HEADER_TIMEDATE		10
-#define LOCAL_FILE_HEADER_CRC32			14
-#define LOCAL_FILE_HEADER_COMPRESSED_SIZE	18
-#define LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE	22
-#define LOCAL_FILE_HEADER_FILENAME_LENGTH	26
-#define LOCAL_FILE_HEADER_EXTRA_LENGTH		28
-#define SIZE_LOCAL_FILE_HEADER			30
-
-#define FILE_HEADER_SIGNATURE			0
-#define FILE_HEADER_VERSION_BY			4
-#define FILE_HEADER_VERSION_EXTRACT		6
-#define FILE_HEADER_FLAGS			8
-#define FILE_HEADER_COMPRESSION			10
-#define FILE_HEADER_TIMEDATE			12
-#define FILE_HEADER_CRC32			16
-#define FILE_HEADER_COMPRESSED_SIZE		20
-#define FILE_HEADER_UNCOMPRESSED_SIZE		24
-#define FILE_HEADER_FILENAME_LENGTH		28
-#define FILE_HEADER_EXTRA_LENGTH		30
-#define FILE_HEADER_COMMENT_LENGTH		32
-#define FILE_HEADER_DISK_NUMBER			34
-#define FILE_HEADER_ATTRIBUTES_INTERNAL		36
-#define FILE_HEADER_ATTRIBUTES_EXTERNAL		38
-#define FILE_HEADER_OFFSET			42
-#define SIZE_FILE_HEADER			46
-
-	/* Not mandatory, but recommended by specification. */
-#define DATA_DESCRIPTOR_SIGNATURE		0
-#define DATA_DESCRIPTOR_CRC32			4
-#define DATA_DESCRIPTOR_COMPRESSED_SIZE		8
-#define DATA_DESCRIPTOR_UNCOMPRESSED_SIZE	12
-#define SIZE_DATA_DESCRIPTOR			16
-
-#define EXTRA_DATA_LOCAL_TIME_ID		0
-#define EXTRA_DATA_LOCAL_TIME_SIZE		2
-#define EXTRA_DATA_LOCAL_TIME_FLAG		4
-#define EXTRA_DATA_LOCAL_MTIME			5
-#define EXTRA_DATA_LOCAL_ATIME			9
-#define EXTRA_DATA_LOCAL_CTIME			13
-#define EXTRA_DATA_LOCAL_UNIX_ID		17
-#define EXTRA_DATA_LOCAL_UNIX_SIZE		19
-#define EXTRA_DATA_LOCAL_UNIX_VERSION		21
-#define EXTRA_DATA_LOCAL_UNIX_UID_SIZE		22
-#define EXTRA_DATA_LOCAL_UNIX_UID		23
-#define EXTRA_DATA_LOCAL_UNIX_GID_SIZE		27
-#define EXTRA_DATA_LOCAL_UNIX_GID		28
-#define SIZE_EXTRA_DATA_LOCAL			32
-
-#define EXTRA_DATA_CENTRAL_TIME_ID		0
-#define EXTRA_DATA_CENTRAL_TIME_SIZE		2
-#define EXTRA_DATA_CENTRAL_TIME_FLAG		4
-#define EXTRA_DATA_CENTRAL_MTIME		5
-#define EXTRA_DATA_CENTRAL_UNIX_ID		9
-#define EXTRA_DATA_CENTRAL_UNIX_SIZE		11
-#define SIZE_EXTRA_DATA_CENTRAL			13
-
-#define CENTRAL_DIRECTORY_END_SIGNATURE		0
-#define CENTRAL_DIRECTORY_END_DISK		4
-#define CENTRAL_DIRECTORY_END_START_DISK	6
-#define CENTRAL_DIRECTORY_END_ENTRIES_DISK	8
-#define CENTRAL_DIRECTORY_END_ENTRIES		10
-#define CENTRAL_DIRECTORY_END_SIZE		12
-#define CENTRAL_DIRECTORY_END_OFFSET		16
-#define CENTRAL_DIRECTORY_END_COMMENT_LENGTH	20
-#define SIZE_CENTRAL_DIRECTORY_END		22
-
-struct zip_file_header_link {
-	struct zip_file_header_link *next;
-	struct archive_entry *entry;
-	int64_t offset;
-	unsigned long crc32;
-	int64_t compressed_size;
-	enum compression compression;
-	int flags;
-};
+static unsigned char *
+cd_alloc(struct zip *zip, size_t length)
+{
+	unsigned char *p;
+
+	if (zip->central_directory == NULL
+	    || (zip->central_directory_last->p + length
+		> zip->central_directory_last->buff + zip->central_directory_last->buff_size)) {
+		struct cd_segment *segment = calloc(1, sizeof(*segment));
+		if (segment == NULL)
+			return NULL;
+		segment->buff_size = 64 * 1024;
+		segment->buff = malloc(segment->buff_size);
+		if (segment->buff == NULL) {
+			free(segment);
+			return NULL;
+		}
+		segment->p = segment->buff;
 
-struct zip {
-	uint8_t data_descriptor[SIZE_DATA_DESCRIPTOR];
-	struct zip_file_header_link *central_directory;
-	struct zip_file_header_link *central_directory_end;
-	int64_t offset;
-	int64_t written_bytes;
-	int64_t remaining_data_bytes;
-	enum compression compression;
-	int flags;
-	struct archive_string_conv *opt_sconv;
-	struct archive_string_conv *sconv_default;
-	int	init_default_conversion;
+		if (zip->central_directory == NULL) {
+			zip->central_directory
+			    = zip->central_directory_last
+			    = segment;
+		} else {
+			zip->central_directory_last->next = segment;
+			zip->central_directory_last = segment;
+		}
+	}
 
-#ifdef HAVE_ZLIB_H
-	z_stream stream;
-	size_t len_buf;
-	unsigned char *buf;
-#endif
-};
+	p = zip->central_directory_last->p;
+	zip->central_directory_last->p += length;
+	zip->central_directory_bytes += length;
+	return (p);
+}
+
+static unsigned long
+real_crc32(unsigned long crc, const void *buff, size_t len)
+{
+	return crc32(crc, buff, len);
+}
+
+static unsigned long
+fake_crc32(unsigned long crc, const void *buff, size_t len)
+{
+	(void)crc; /* UNUSED */
+	(void)buff; /* UNUSED */
+	(void)len; /* UNUSED */
+	return 0;
+}
 
 static int
 archive_write_zip_options(struct archive_write *a, const char *key,
@@ -217,24 +206,49 @@ archive_write_zip_options(struct archive_write *a, const char *key,
 	int ret = ARCHIVE_FAILED;
 
 	if (strcmp(key, "compression") == 0) {
+		/*
+		 * Set compression to use on all future entries.
+		 * This only affects regular files.
+		 */
 		if (val == NULL || val[0] == 0) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "%s: compression option needs a compression name",
 			    a->format_name);
 		} else if (strcmp(val, "deflate") == 0) {
 #ifdef HAVE_ZLIB_H
-			zip->compression = COMPRESSION_DEFLATE;
+			zip->requested_compression = COMPRESSION_DEFLATE;
 			ret = ARCHIVE_OK;
 #else
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "deflate compression not supported");
 #endif
 		} else if (strcmp(val, "store") == 0) {
-			zip->compression = COMPRESSION_STORE;
+			zip->requested_compression = COMPRESSION_STORE;
 			ret = ARCHIVE_OK;
 		}
 		return (ret);
+	} else if (strcmp(key, "experimental") == 0) {
+		if (val == NULL || val[0] == 0) {
+			zip->flags &= ~ ZIP_FLAG_EXPERIMENT_EL;
+		} else {
+			zip->flags |= ZIP_FLAG_EXPERIMENT_EL;
+		}
+		return (ARCHIVE_OK);
+	} else if (strcmp(key, "fakecrc32") == 0) {
+		/*
+		 * FOR TESTING ONLY:  disable CRC calculation to speed up
+		 * certain complex tests.
+		 */
+		if (val == NULL || val[0] == 0) {
+			zip->crc32func = real_crc32;
+		} else {
+			zip->crc32func = fake_crc32;
+		}
+		return (ARCHIVE_OK);
 	} else if (strcmp(key, "hdrcharset")  == 0) {
+		/*
+		 * Set the character set used in translating filenames.
+		 */
 		if (val == NULL || val[0] == 0) {
 			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			    "%s: hdrcharset option needs a character-set name",
@@ -248,6 +262,21 @@ archive_write_zip_options(struct archive_write *a, const char *key,
 				ret = ARCHIVE_FATAL;
 		}
 		return (ret);
+	} else if (strcmp(key, "zip64") == 0) {
+		/*
+		 * Bias decisions about Zip64: force them to be
+		 * generated in certain cases where they are not
+		 * forbidden or avoid them in certain cases where they
+		 * are not strictly required.
+		 */
+		if (val != NULL && *val != '\0') {
+			zip->flags |= ZIP_FLAG_FORCE_ZIP64;
+			zip->flags &= ~ZIP_FLAG_AVOID_ZIP64;
+		} else {
+			zip->flags &= ~ZIP_FLAG_FORCE_ZIP64;
+			zip->flags |= ZIP_FLAG_AVOID_ZIP64;
+		}
+		return (ARCHIVE_OK);
 	}
 
 	/* Note: The "warn" return is just to inform the options
@@ -261,9 +290,9 @@ archive_write_zip_set_compression_deflate(struct archive *_a)
 {
 	struct archive_write *a = (struct archive_write *)_a;
 	int ret = ARCHIVE_FAILED;
-	
+
 	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
-		ARCHIVE_STATE_NEW | ARCHIVE_STATE_HEADER,
+		ARCHIVE_STATE_NEW | ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
 		"archive_write_zip_set_compression_deflate");
 	if (a->archive.archive_format != ARCHIVE_FORMAT_ZIP) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
@@ -273,11 +302,12 @@ archive_write_zip_set_compression_deflate(struct archive *_a)
 	} else {
 #ifdef HAVE_ZLIB_H
 		struct zip *zip = a->format_data;
-		zip->compression = COMPRESSION_DEFLATE;
+		zip->requested_compression = COMPRESSION_DEFLATE;
 		ret = ARCHIVE_OK;
 #else
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			"deflate compression not supported");
+		ret = ARCHIVE_FAILED;
 #endif
 	}
 	return (ret);
@@ -289,17 +319,17 @@ archive_write_zip_set_compression_store(struct archive *_a)
 	struct archive_write *a = (struct archive_write *)_a;
 	struct zip *zip = a->format_data;
 	int ret = ARCHIVE_FAILED;
-	
+
 	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
-		ARCHIVE_STATE_NEW | ARCHIVE_STATE_HEADER,
+		ARCHIVE_STATE_NEW | ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
 		"archive_write_zip_set_compression_deflate");
 	if (a->archive.archive_format != ARCHIVE_FORMAT_ZIP) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 			"Can only use archive_write_zip_set_compression_store"
 			" with zip format");
 		ret = ARCHIVE_FATAL;
 	} else {
-		zip->compression = COMPRESSION_STORE;
+		zip->requested_compression = COMPRESSION_STORE;
 		ret = ARCHIVE_OK;
 	}
 	return (ret);
@@ -324,14 +354,12 @@ archive_write_set_format_zip(struct archive *_a)
 		    "Can't allocate zip data");
 		return (ARCHIVE_FATAL);
 	}
-	zip->central_directory = NULL;
-	zip->central_directory_end = NULL;
-	zip->offset = 0;
-	zip->written_bytes = 0;
-	zip->remaining_data_bytes = 0;
+
+	/* "Unspecified" lets us choose the appropriate compression. */
+	zip->requested_compression = COMPRESSION_UNSPECIFIED;
+	zip->crc32func = real_crc32;
 
 #ifdef HAVE_ZLIB_H
-	zip->compression = COMPRESSION_DEFLATE;
 	zip->len_buf = 65536;
 	zip->buf = malloc(zip->len_buf);
 	if (zip->buf == NULL) {
@@ -340,8 +368,6 @@ archive_write_set_format_zip(struct archive *_a)
 		    "Can't allocate compression buffer");
 		return (ARCHIVE_FATAL);
 	}
-#else
-	zip->compression = COMPRESSION_STORE;
 #endif
 
 	a->format_data = zip;
@@ -355,9 +381,6 @@ archive_write_set_format_zip(struct archive *_a)
 	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
 	a->archive.archive_format_name = "ZIP";
 
-	archive_le32enc(&zip->data_descriptor[DATA_DESCRIPTOR_SIGNATURE],
-	    ZIP_SIGNATURE_DATA_DESCRIPTOR);
-
 	return (ARCHIVE_OK);
 }
 
@@ -376,88 +399,86 @@ is_all_ascii(const char *p)
 static int
 archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 {
-	struct zip *zip;
-	uint8_t h[SIZE_LOCAL_FILE_HEADER];
-	uint8_t e[SIZE_EXTRA_DATA_LOCAL];
-	uint8_t *d;
-	struct zip_file_header_link *l;
-	struct archive_string_conv *sconv;
+	unsigned char local_header[32];
+	unsigned char local_extra[128];
+	struct zip *zip = a->format_data;
+	unsigned char *e;
+	unsigned char *cd_extra;
+	size_t filename_length;
+	const char *symlink = NULL;
+	size_t symlink_size = 0;
+	struct archive_string_conv *sconv = get_sconv(a, zip);
 	int ret, ret2 = ARCHIVE_OK;
 	int64_t size;
 	mode_t type;
+	int version_needed = 10;
 
-	/* Entries other than a regular file or a folder are skipped. */
+	/* Ignore types of entries that we don't support. */
 	type = archive_entry_filetype(entry);
 	if (type != AE_IFREG && type != AE_IFDIR && type != AE_IFLNK) {
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Filetype not supported");
 		return ARCHIVE_FAILED;
 	};
 
-	/* Directory entries should have a size of 0. */
-	if (type == AE_IFDIR)
+	/* If we're not using Zip64, reject large files. */
+	if (zip->flags & ZIP_FLAG_AVOID_ZIP64) {
+		/* Reject entries over 4GB. */
+		if (archive_entry_size_is_set(entry)
+		    && (archive_entry_size(entry) > 0xffffffff)) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Files > 4GB require Zip64 extensions");
+			return ARCHIVE_FAILED;
+		}
+		/* Reject entries if archive is > 4GB. */
+		if (zip->written_bytes > 0xffffffff) {
+			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+			    "Archives > 4GB require Zip64 extensions");
+			return ARCHIVE_FAILED;
+		}
+	}
+
+	/* Only regular files can have size > 0. */
+	if (type != AE_IFREG)
 		archive_entry_set_size(entry, 0);
 
-	zip = a->format_data;
-	/* Setup default conversion. */
-	if (zip->opt_sconv == NULL && !zip->init_default_conversion) {
-		zip->sconv_default =
-		    archive_string_default_conversion_for_write(&(a->archive));
-		zip->init_default_conversion = 1;
-	}
 
-	if (zip->flags == 0) {
-		/* Initialize the general purpose flags. */
-		zip->flags = ZIP_FLAGS;
-		if (zip->opt_sconv != NULL) {
-			if (strcmp(archive_string_conversion_charset_name(
-			    zip->opt_sconv), "UTF-8") == 0)
-				zip->flags |= ZIP_FLAGS_UTF8_NAME;
-#if HAVE_NL_LANGINFO
-		} else if (strcmp(nl_langinfo(CODESET), "UTF-8") == 0) {
-			zip->flags |= ZIP_FLAGS_UTF8_NAME;
-#endif
-		}
+	/* Reset information from last entry. */
+	zip->entry_offset = zip->written_bytes;
+	zip->entry_uncompressed_limit = INT64_MAX;
+	zip->entry_compressed_size = 0;
+	zip->entry_uncompressed_size = 0;
+	zip->entry_compressed_written = 0;
+	zip->entry_uncompressed_written = 0;
+	zip->entry_flags = 0;
+	zip->entry_uses_zip64 = 0;
+	zip->entry_crc32 = zip->crc32func(0, NULL, 0);
+	if (zip->entry != NULL) {
+		archive_entry_free(zip->entry);
+		zip->entry = NULL;
 	}
-	d = zip->data_descriptor;
-	size = archive_entry_size(entry);
-	zip->remaining_data_bytes = size;
 
-	/* Append archive entry to the central directory data. */
-	l = (struct zip_file_header_link *) malloc(sizeof(*l));
-	if (l == NULL) {
-		archive_set_error(&a->archive, ENOMEM,
-		    "Can't allocate zip header data");
-		return (ARCHIVE_FATAL);
-	}
 #if defined(_WIN32) && !defined(__CYGWIN__)
 	/* Make sure the path separators in pahtname, hardlink and symlink
 	 * are all slash '/', not the Windows path separator '\'. */
-	l->entry = __la_win_entry_in_posix_pathseparator(entry);
-	if (l->entry == entry)
-		l->entry = archive_entry_clone(entry);
+	zip->entry = __la_win_entry_in_posix_pathseparator(entry);
+	if (zip->entry == entry)
+		zip->entry = archive_entry_clone(entry);
 #else
-	l->entry = archive_entry_clone(entry);
+	zip->entry = archive_entry_clone(entry);
 #endif
-	if (l->entry == NULL) {
+	if (zip->entry == NULL) {
 		archive_set_error(&a->archive, ENOMEM,
 		    "Can't allocate zip header data");
-		free(l);
 		return (ARCHIVE_FATAL);
 	}
-	l->flags = zip->flags;
-	if (zip->opt_sconv != NULL)
-		sconv = zip->opt_sconv;
-	else
-		sconv = zip->sconv_default;
+
 	if (sconv != NULL) {
 		const char *p;
 		size_t len;
 
 		if (archive_entry_pathname_l(entry, &p, &len, sconv) != 0) {
 			if (errno == ENOMEM) {
-				archive_entry_free(l->entry);
-				free(l);
 				archive_set_error(&a->archive, ENOMEM,
 				    "Can't allocate memory for Pathname");
 				return (ARCHIVE_FATAL);
@@ -470,186 +491,305 @@ archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
 			ret2 = ARCHIVE_WARN;
 		}
 		if (len > 0)
-			archive_entry_set_pathname(l->entry, p);
+			archive_entry_set_pathname(zip->entry, p);
 
 		/*
-		 * Although there is no character-set regulation for Symlink,
-		 * it is suitable to convert a character-set of Symlinke to
-		 * what those of the Pathname has been converted to.
+		 * There is no standard for symlink handling; we convert
+		 * it using the same character-set translation that we use
+		 * for filename.
 		 */
 		if (type == AE_IFLNK) {
 			if (archive_entry_symlink_l(entry, &p, &len, sconv)) {
 				if (errno == ENOMEM) {
-					archive_entry_free(l->entry);
-					free(l);
 					archive_set_error(&a->archive, ENOMEM,
 					    "Can't allocate memory "
 					    " for Symlink");
 					return (ARCHIVE_FATAL);
 				}
-				/*
-				 * Even if the strng conversion failed,
-				 * we should not report the error since
-				 * thre is no regulation for.
-				 */
+				/* No error if we can't convert. */
 			} else if (len > 0)
-				archive_entry_set_symlink(l->entry, p);
+				archive_entry_set_symlink(zip->entry, p);
+		}
+	}
+
+	/* If filename isn't ASCII and we can use UTF-8, set the UTF-8 flag. */
+	if (!is_all_ascii(archive_entry_pathname(zip->entry))) {
+		if (zip->opt_sconv != NULL) {
+			if (strcmp(archive_string_conversion_charset_name(
+					zip->opt_sconv), "UTF-8") == 0)
+				zip->entry_flags |= ZIP_ENTRY_FLAG_UTF8_NAME;
+#if HAVE_NL_LANGINFO
+		} else if (strcmp(nl_langinfo(CODESET), "UTF-8") == 0) {
+			zip->entry_flags |= ZIP_ENTRY_FLAG_UTF8_NAME;
+#endif
 		}
 	}
-	/* If all characters in a filename are ASCII, Reset UTF-8 Name flag. */
-	if ((l->flags & ZIP_FLAGS_UTF8_NAME) != 0 &&
-	    is_all_ascii(archive_entry_pathname(l->entry)))
-		l->flags &= ~ZIP_FLAGS_UTF8_NAME;
+	filename_length = path_length(zip->entry);
 
-	/* Initialize the CRC variable and potentially the local crc32(). */
-	l->crc32 = crc32(0, NULL, 0);
+	/* Determine appropriate compression and size for this entry. */
 	if (type == AE_IFLNK) {
-		const char *p = archive_entry_symlink(l->entry);
-		if (p != NULL)
-			size = strlen(p);
+		symlink = archive_entry_symlink(zip->entry);
+		if (symlink != NULL)
+			symlink_size = strlen(symlink);
 		else
-			size = 0;
-		zip->remaining_data_bytes = 0;
-		archive_entry_set_size(l->entry, size);
-		l->compression = COMPRESSION_STORE;
-		l->compressed_size = size;
+			symlink_size = 0;
+		zip->entry_uncompressed_limit = symlink_size;
+		zip->entry_compressed_size = symlink_size;
+		zip->entry_uncompressed_size = symlink_size;
+		zip->entry_crc32 = zip->crc32func(zip->entry_crc32,
+		    (const unsigned char *)symlink, symlink_size);
+		zip->entry_compression = COMPRESSION_STORE;
+		version_needed = 20;
+	} else if (type != AE_IFREG) {
+		zip->entry_compression = COMPRESSION_STORE;
+		zip->entry_uncompressed_limit = 0;
+		size = 0;
+		version_needed = 20;
+	} else if (archive_entry_size_is_set(zip->entry)) {
+		size = archive_entry_size(zip->entry);
+		zip->entry_uncompressed_limit = size;
+		zip->entry_compression = zip->requested_compression;
+		if (zip->entry_compression == COMPRESSION_UNSPECIFIED) {
+			zip->entry_compression = COMPRESSION_DEFAULT;
+		}
+		if (zip->entry_compression == COMPRESSION_STORE) {
+			zip->entry_compressed_size = size;
+			zip->entry_uncompressed_size = size;
+			version_needed = 10;
+		} else {
+			zip->entry_uncompressed_size = size;
+			version_needed = 20;
+		}
+		if ((zip->flags & ZIP_FLAG_FORCE_ZIP64) /* User asked. */
+		    || (zip->entry_uncompressed_size > 0xffffffffLL)) { /* Large entry. */
+			zip->entry_uses_zip64 = 1;
+			version_needed = 45;
+		}
+
+		/* We may know the size, but never the CRC. */
+		zip->entry_flags |= ZIP_ENTRY_FLAG_LENGTH_AT_END;
 	} else {
-		l->compression = zip->compression;
-		l->compressed_size = 0;
+		/* Prefer deflate if it's available, because deflate
+		 * has a clear end-of-data marker that makes
+		 * length-at-end more reliable. */
+		zip->entry_compression = COMPRESSION_DEFAULT;
+		zip->entry_flags |= ZIP_ENTRY_FLAG_LENGTH_AT_END;
+		if ((zip->flags & ZIP_FLAG_AVOID_ZIP64) == 0) {
+			zip->entry_uses_zip64 = 1;
+			version_needed = 45;
+		} else if (zip->entry_compression == COMPRESSION_STORE) {
+			version_needed = 10;
+		} else {
+			version_needed = 20;
+		}
 	}
-	l->next = NULL;
-	if (zip->central_directory == NULL) {
-		zip->central_directory = l;
+
+	/* Format the local header. */
+	memset(local_header, 0, sizeof(local_header));
+	memcpy(local_header, "PK\003\004", 4);
+	archive_le16enc(local_header + 4, version_needed);
+	archive_le16enc(local_header + 6, zip->entry_flags);
+	archive_le16enc(local_header + 8, zip->entry_compression);
+	archive_le32enc(local_header + 10, dos_time(archive_entry_mtime(zip->entry)));
+	archive_le32enc(local_header + 14, zip->entry_crc32);
+	if (zip->entry_uses_zip64) {
+		/* Zip64 data in the local header "must" include both
+		 * compressed and uncompressed sizes AND those fields
+		 * are included only if these are 0xffffffff;
+		 * THEREFORE these must be set this way, even if we
+		 * know one of them is smaller. */
+		archive_le32enc(local_header + 18, 0xffffffffLL);
+		archive_le32enc(local_header + 22, 0xffffffffLL);
 	} else {
-		zip->central_directory_end->next = l;
-	}
-	zip->central_directory_end = l;
-
-	/* Store the offset of this header for later use in central
-	 * directory. */
-	l->offset = zip->written_bytes;
-
-	memset(h, 0, sizeof(h));
-	archive_le32enc(&h[LOCAL_FILE_HEADER_SIGNATURE],
-		ZIP_SIGNATURE_LOCAL_FILE_HEADER);
-	archive_le16enc(&h[LOCAL_FILE_HEADER_VERSION], ZIP_VERSION_EXTRACT);
-	archive_le16enc(&h[LOCAL_FILE_HEADER_FLAGS], l->flags);
-	archive_le16enc(&h[LOCAL_FILE_HEADER_COMPRESSION], l->compression);
-	archive_le32enc(&h[LOCAL_FILE_HEADER_TIMEDATE],
-		dos_time(archive_entry_mtime(entry)));
-	archive_le16enc(&h[LOCAL_FILE_HEADER_FILENAME_LENGTH],
-		(uint16_t)path_length(l->entry));
-
-	switch (l->compression) {
-	case COMPRESSION_STORE:
-		/* Setting compressed and uncompressed sizes even when
-		 * specification says to set to zero when using data
-		 * descriptors. Otherwise the end of the data for an
-		 * entry is rather difficult to find. */
-		archive_le32enc(&h[LOCAL_FILE_HEADER_COMPRESSED_SIZE],
-		    (uint32_t)size);
-		archive_le32enc(&h[LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE],
-		    (uint32_t)size);
-		break;
-#ifdef HAVE_ZLIB_H
-	case COMPRESSION_DEFLATE:
-		archive_le32enc(&h[LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE],
-		    (uint32_t)size);
+		archive_le32enc(local_header + 18, zip->entry_compressed_size);
+		archive_le32enc(local_header + 22, zip->entry_uncompressed_size);
+	}
+	archive_le16enc(local_header + 26, filename_length);
+
+	/* Format as much of central directory file header as we can: */
+	zip->file_header = cd_alloc(zip, 46);
+	/* If (zip->file_header == NULL) XXXX */
+	++zip->central_directory_entries;
+	memset(zip->file_header, 0, 46);
+	memcpy(zip->file_header, "PK\001\002", 4);
+	/* "Made by PKZip 2.0 on Unix." */
+	archive_le16enc(zip->file_header + 4, 3 * 256 + version_needed);
+	archive_le16enc(zip->file_header + 6, version_needed);
+	archive_le16enc(zip->file_header + 8, zip->entry_flags);
+	archive_le16enc(zip->file_header + 10, zip->entry_compression);
+	archive_le32enc(zip->file_header + 12, dos_time(archive_entry_mtime(zip->entry)));
+	archive_le16enc(zip->file_header + 28, filename_length);
+	/* Following Info-Zip, store mode in the "external attributes" field. */
+	archive_le32enc(zip->file_header + 38,
+	    archive_entry_mode(zip->entry) << 16);
+	e = cd_alloc(zip, filename_length);
+	/* If (e == NULL) XXXX */
+	copy_path(zip->entry, e);
+
+	/* Format extra data. */
+	memset(local_extra, 0, sizeof(local_extra));
+	e = local_extra;
+
+	/* First, extra blocks that are the same between
+	 * the local file header and the central directory.
+	 * We format them once and then duplicate them. */
+
+	/* UT timestamp, length depends on what timestamps are set. */
+	memcpy(e, "UT", 2);
+	archive_le16enc(e + 2,
+	    1
+	    + (archive_entry_mtime_is_set(entry) ? 4 : 0)
+	    + (archive_entry_atime_is_set(entry) ? 4 : 0)
+	    + (archive_entry_ctime_is_set(entry) ? 4 : 0));
+	e += 4;
+	*e++ =
+	    (archive_entry_mtime_is_set(entry) ? 1 : 0)
+	    | (archive_entry_atime_is_set(entry) ? 2 : 0)
+	    | (archive_entry_ctime_is_set(entry) ? 4 : 0);
+	if (archive_entry_mtime_is_set(entry)) {
+		archive_le32enc(e, (uint32_t)archive_entry_mtime(entry));
+		e += 4;
+	}
+	if (archive_entry_atime_is_set(entry)) {
+		archive_le32enc(e, (uint32_t)archive_entry_atime(entry));
+		e += 4;
+	}
+	if (archive_entry_ctime_is_set(entry)) {
+		archive_le32enc(e, (uint32_t)archive_entry_ctime(entry));
+		e += 4;
+	}
 
-		zip->stream.zalloc = Z_NULL;
-		zip->stream.zfree = Z_NULL;
-		zip->stream.opaque = Z_NULL;
-		zip->stream.next_out = zip->buf;
-		zip->stream.avail_out = (uInt)zip->len_buf;
-		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,
-		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
-			archive_set_error(&a->archive, ENOMEM,
-			    "Can't init deflate compressor");
-			return (ARCHIVE_FATAL);
+	/* ux Unix extra data, length 11, version 1 */
+	/* TODO: If uid < 64k, use 2 bytes, ditto for gid. */
+	memcpy(e, "ux\013\000\001", 5);
+	e += 5;
+	*e++ = 4; /* Length of following UID */
+	archive_le32enc(e, (uint32_t)archive_entry_uid(entry));
+	e += 4;
+	*e++ = 4; /* Length of following GID */
+	archive_le32enc(e, (uint32_t)archive_entry_gid(entry));
+	e += 4;
+
+	/* Copy UT and ux into central directory as well. */
+	zip->file_header_extra_offset = zip->central_directory_bytes;
+	cd_extra = cd_alloc(zip, e - local_extra);
+	memcpy(cd_extra, local_extra, e - local_extra);
+
+	/*
+	 * Following extra blocks vary between local header and
+	 * central directory. These are the local header versions.
+	 * Central directory versions get formatted in
+	 * archive_write_zip_finish_entry() below.
+	 */
+
+	/* "[Zip64 entry] in the local header MUST include BOTH
+	 * original [uncompressed] and compressed size fields." */
+	if (zip->entry_uses_zip64) {
+		unsigned char *zip64_start = e;
+		memcpy(e, "\001\000\020\000", 4);
+		e += 4;
+		archive_le64enc(e, zip->entry_uncompressed_size);
+		e += 8;
+		archive_le64enc(e, zip->entry_compressed_size);
+		e += 8;
+		archive_le16enc(zip64_start + 2, e - (zip64_start + 4));
+	}
+
+	if (zip->flags & ZIP_FLAG_EXPERIMENT_EL) {
+		/* Experimental 'el' extension to improve streaming. */
+		unsigned char *external_info = e;
+		int included = 7;
+		memcpy(e, "el\000\000", 4); // 0x6c65 + 2-byte length
+		e += 4;
+		e[0] = included; /* bitmap of included fields */
+		e += 1;
+		if (included & 1) {
+			archive_le16enc(e, /* "Version created by" */
+			    3 * 256 + version_needed);
+			e += 2;
 		}
-		break;
-#endif
+		if (included & 2) {
+			archive_le16enc(e, 0); /* internal file attributes */
+			e += 2;
+		}
+		if (included & 4) {
+			archive_le32enc(e,  /* external file attributes */
+			    archive_entry_mode(zip->entry) << 16);
+			e += 4;
+		}
+		if (included & 8) {
+			// Libarchive does not currently support file comments.
+		}
+		archive_le16enc(external_info + 2, e - (external_info + 4));
 	}
 
-	/* Formatting extra data. */
-	archive_le16enc(&h[LOCAL_FILE_HEADER_EXTRA_LENGTH], sizeof(e));
-	archive_le16enc(&e[EXTRA_DATA_LOCAL_TIME_ID],
-		ZIP_SIGNATURE_EXTRA_TIMESTAMP);
-	archive_le16enc(&e[EXTRA_DATA_LOCAL_TIME_SIZE], 1 + 4 * 3);
-	e[EXTRA_DATA_LOCAL_TIME_FLAG] = 0x07;
-	archive_le32enc(&e[EXTRA_DATA_LOCAL_MTIME],
-	    (uint32_t)archive_entry_mtime(entry));
-	archive_le32enc(&e[EXTRA_DATA_LOCAL_ATIME],
-	    (uint32_t)archive_entry_atime(entry));
-	archive_le32enc(&e[EXTRA_DATA_LOCAL_CTIME],
-	    (uint32_t)archive_entry_ctime(entry));
-
-	archive_le16enc(&e[EXTRA_DATA_LOCAL_UNIX_ID],
-		ZIP_SIGNATURE_EXTRA_NEW_UNIX);
-	archive_le16enc(&e[EXTRA_DATA_LOCAL_UNIX_SIZE], 1 + (1 + 4) * 2);
-	e[EXTRA_DATA_LOCAL_UNIX_VERSION] = 1;
-	e[EXTRA_DATA_LOCAL_UNIX_UID_SIZE] = 4;
-	archive_le32enc(&e[EXTRA_DATA_LOCAL_UNIX_UID],
-		(uint32_t)archive_entry_uid(entry));
-	e[EXTRA_DATA_LOCAL_UNIX_GID_SIZE] = 4;
-	archive_le32enc(&e[EXTRA_DATA_LOCAL_UNIX_GID],
-		(uint32_t)archive_entry_gid(entry));
-
-	archive_le32enc(&d[DATA_DESCRIPTOR_UNCOMPRESSED_SIZE],
-	    (uint32_t)size);
-
-	ret = __archive_write_output(a, h, sizeof(h));
+	/* Update local header with size of extra data and write it all out: */
+	archive_le16enc(local_header + 28, e - local_extra);
+
+	ret = __archive_write_output(a, local_header, 30);
 	if (ret != ARCHIVE_OK)
 		return (ARCHIVE_FATAL);
-	zip->written_bytes += sizeof(h);
+	zip->written_bytes += 30;
 
-	ret = write_path(l->entry, a);
+	ret = write_path(zip->entry, a);
 	if (ret <= ARCHIVE_OK)
 		return (ARCHIVE_FATAL);
 	zip->written_bytes += ret;
 
-	ret = __archive_write_output(a, e, sizeof(e));
+	ret = __archive_write_output(a, local_extra, e - local_extra);
 	if (ret != ARCHIVE_OK)
 		return (ARCHIVE_FATAL);
-	zip->written_bytes += sizeof(e);
-
-	if (type == AE_IFLNK) {
-		const unsigned char *p;
+	zip->written_bytes += e - local_extra;
 
-		p = (const unsigned char *)archive_entry_symlink(l->entry);
-		ret = __archive_write_output(a, p, (size_t)size);
+	/* For symlinks, write the body now. */
+	if (symlink != NULL) {
+		ret = __archive_write_output(a, symlink, (size_t)symlink_size);
 		if (ret != ARCHIVE_OK)
 			return (ARCHIVE_FATAL);
-		zip->written_bytes += size;
-		l->crc32 = crc32(l->crc32, p, (unsigned)size);
+		zip->entry_compressed_written += symlink_size;
+		zip->entry_uncompressed_written += symlink_size;
+		zip->written_bytes += symlink_size;
 	}
 
-	if (ret2 != ARCHIVE_OK)
-		return (ret2);
-	return (ARCHIVE_OK);
+#ifdef HAVE_ZLIB_H
+	if (zip->entry_compression == COMPRESSION_DEFLATE) {
+		zip->stream.zalloc = Z_NULL;
+		zip->stream.zfree = Z_NULL;
+		zip->stream.opaque = Z_NULL;
+		zip->stream.next_out = zip->buf;
+		zip->stream.avail_out = (uInt)zip->len_buf;
+		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,
+		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
+			archive_set_error(&a->archive, ENOMEM,
+			    "Can't init deflate compressor");
+			return (ARCHIVE_FATAL);
+		}
+	}
+#endif
+
+	return (ret2);
 }
 
 static ssize_t
 archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 {
 	int ret;
 	struct zip *zip = a->format_data;
-	struct zip_file_header_link *l = zip->central_directory_end;
 
-	if ((int64_t)s > zip->remaining_data_bytes)
-		s = (size_t)zip->remaining_data_bytes;
+	if ((int64_t)s > zip->entry_uncompressed_limit)
+		s = (size_t)zip->entry_uncompressed_limit;
+	zip->entry_uncompressed_written += s;
 
 	if (s == 0) return 0;
 
-	switch (l->compression) {
+	switch (zip->entry_compression) {
 	case COMPRESSION_STORE:
 		ret = __archive_write_output(a, buff, s);
-		if (ret != ARCHIVE_OK) return (ret);
+		if (ret != ARCHIVE_OK)
+			return (ret);
 		zip->written_bytes += s;
-		zip->remaining_data_bytes -= s;
-		l->compressed_size += s;
-		l->crc32 = crc32(l->crc32, buff, (unsigned)s);
-		return (s);
+		zip->entry_compressed_written += s;
+		break;
 #if HAVE_ZLIB_H
 	case COMPRESSION_DEFLATE:
 		zip->stream.next_in = (unsigned char*)(uintptr_t)buff;
@@ -663,189 +803,210 @@ archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)
 					zip->len_buf);
 				if (ret != ARCHIVE_OK)
 					return (ret);
-				l->compressed_size += zip->len_buf;
+				zip->entry_compressed_written += zip->len_buf;
 				zip->written_bytes += zip->len_buf;
 				zip->stream.next_out = zip->buf;
 				zip->stream.avail_out = (uInt)zip->len_buf;
 			}
 		} while (zip->stream.avail_in != 0);
-		zip->remaining_data_bytes -= s;
-		/* If we have it, use zlib's fast crc32() */
-		l->crc32 = crc32(l->crc32, buff, (uInt)s);
-		return (s);
+		break;
 #endif
 
 	default:
 		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
 		    "Invalid ZIP compression type");
 		return ARCHIVE_FATAL;
 	}
+
+	zip->entry_uncompressed_limit -= s;
+	zip->entry_crc32 = zip->crc32func(zip->entry_crc32, buff, (unsigned)s);
+	return (s);
+
 }
 
 static int
 archive_write_zip_finish_entry(struct archive_write *a)
 {
-	/* Write the data descripter after file data has been written. */
-	int ret;
 	struct zip *zip = a->format_data;
-	uint8_t *d = zip->data_descriptor;
-	struct zip_file_header_link *l = zip->central_directory_end;
-#if HAVE_ZLIB_H
-	size_t reminder;
-#endif
+	int ret;
 
-	switch(l->compression) {
-	case COMPRESSION_STORE:
-		break;
 #if HAVE_ZLIB_H
-	case COMPRESSION_DEFLATE:
+	if (zip->entry_compression == COMPRESSION_DEFLATE) {
 		for (;;) {
+			size_t remainder;
 			ret = deflate(&zip->stream, Z_FINISH);
 			if (ret == Z_STREAM_ERROR)
 				return (ARCHIVE_FATAL);
-			reminder = zip->len_buf - zip->stream.avail_out;
-			ret = __archive_write_output(a, zip->buf, reminder);
+			remainder = zip->len_buf - zip->stream.avail_out;
+			ret = __archive_write_output(a, zip->buf, remainder);
 			if (ret != ARCHIVE_OK)
 				return (ret);
-			l->compressed_size += reminder;
-			zip->written_bytes += reminder;
+			zip->entry_compressed_written += remainder;
+			zip->written_bytes += remainder;
 			zip->stream.next_out = zip->buf;
 			if (zip->stream.avail_out != 0)
 				break;
 			zip->stream.avail_out = (uInt)zip->len_buf;
 		}
 		deflateEnd(&zip->stream);
-		break;
+	}
 #endif
+
+	/* Write trailing data descriptor. */
+	if ((zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END) != 0) {
+		char d[24];
+		memcpy(d, "PK\007\010", 4);
+		archive_le32enc(d + 4, zip->entry_crc32);
+		if (zip->entry_uses_zip64) {
+			archive_le64enc(d + 8, (uint64_t)zip->entry_compressed_written);
+			archive_le64enc(d + 16, (uint64_t)zip->entry_uncompressed_written);
+			ret = __archive_write_output(a, d, 24);
+			zip->written_bytes += 24;
+		} else {
+			archive_le32enc(d + 8, (uint32_t)zip->entry_compressed_written);
+			archive_le32enc(d + 12, (uint32_t)zip->entry_uncompressed_written);
+			ret = __archive_write_output(a, d, 16);
+			zip->written_bytes += 16;
+		}
+		if (ret != ARCHIVE_OK)
+			return (ARCHIVE_FATAL);
 	}
 
-	archive_le32enc(&d[DATA_DESCRIPTOR_CRC32], l->crc32);
-	archive_le32enc(&d[DATA_DESCRIPTOR_COMPRESSED_SIZE],
-		(uint32_t)l->compressed_size);
-	ret = __archive_write_output(a, d, SIZE_DATA_DESCRIPTOR);
-	if (ret != ARCHIVE_OK)
-		return (ARCHIVE_FATAL);
-	zip->written_bytes += SIZE_DATA_DESCRIPTOR;
+	/* Append Zip64 extra data to central directory information. */
+	if (zip->entry_compressed_written > 0xffffffffLL
+	    || zip->entry_uncompressed_written > 0xffffffffLL
+	    || zip->entry_offset > 0xffffffffLL) {
+		unsigned char zip64[32];
+		unsigned char *z = zip64, *zd;
+		memcpy(z, "\001\000\000\000", 4);
+		z += 4;
+		if (zip->entry_uncompressed_written >= 0xffffffffLL) {
+			archive_le64enc(z, zip->entry_uncompressed_written);
+			z += 8;
+		}
+		if (zip->entry_compressed_written >= 0xffffffffLL) {
+			archive_le64enc(z, zip->entry_compressed_written);
+			z += 8;
+		}
+		if (zip->entry_offset >= 0xffffffffLL) {
+			archive_le64enc(z, zip->entry_offset);
+			z += 8;
+		}
+		archive_le16enc(zip64 + 2, z - (zip64 + 4));
+		zd = cd_alloc(zip, z - zip64);
+		if (zd == NULL) {
+			archive_set_error(&a->archive, ENOMEM,
+				"Can't allocate zip data");
+			return (ARCHIVE_FATAL);
+		}
+		memcpy(zd, zip64, z - zip64);
+		/* Zip64 means version needs to be set to at least 4.5 */
+		if (archive_le16dec(zip->file_header + 6) < 45)
+			archive_le16enc(zip->file_header + 6, 45);
+	}
+
+	/* Fix up central directory file header. */
+	archive_le32enc(zip->file_header + 16, zip->entry_crc32);
+	archive_le32enc(zip->file_header + 20,
+	    zipmin(zip->entry_compressed_written, 0xffffffffLL));
+	archive_le32enc(zip->file_header + 24,
+	    zipmin(zip->entry_uncompressed_written, 0xffffffffLL));
+	archive_le16enc(zip->file_header + 30,
+	    zip->central_directory_bytes - zip->file_header_extra_offset);
+	archive_le32enc(zip->file_header + 42,
+	    zipmin(zip->entry_offset, 0xffffffffLL));
+
 	return (ARCHIVE_OK);
 }
 
 static int
 archive_write_zip_close(struct archive_write *a)
 {
-	struct zip *zip;
-	struct zip_file_header_link *l;
-	uint8_t h[SIZE_FILE_HEADER];
-	uint8_t end[SIZE_CENTRAL_DIRECTORY_END];
-	uint8_t e[SIZE_EXTRA_DATA_CENTRAL];
+	uint8_t buff[64];
 	int64_t offset_start, offset_end;
-	int entries;
+	struct zip *zip = a->format_data;
+	struct cd_segment *segment;
 	int ret;
 
-	zip = a->format_data;
-	l = zip->central_directory;
-
-	/*
-	 * Formatting central directory file header fields that are
-	 * fixed for all entries.
-	 * Fields not used (and therefor 0) are:
-	 *
-	 *   - comment_length
-	 *   - disk_number
-	 *   - attributes_internal
-	 */
-	memset(h, 0, sizeof(h));
-	archive_le32enc(&h[FILE_HEADER_SIGNATURE], ZIP_SIGNATURE_FILE_HEADER);
-	archive_le16enc(&h[FILE_HEADER_VERSION_BY], ZIP_VERSION_BY);
-	archive_le16enc(&h[FILE_HEADER_VERSION_EXTRACT], ZIP_VERSION_EXTRACT);
-
-	entries = 0;
 	offset_start = zip->written_bytes;
-
-	/* Formatting individual header fields per entry and
-	 * writing each entry. */
-	while (l != NULL) {
-		archive_le16enc(&h[FILE_HEADER_FLAGS], l->flags);
-		archive_le16enc(&h[FILE_HEADER_COMPRESSION], l->compression);
-		archive_le32enc(&h[FILE_HEADER_TIMEDATE],
-			dos_time(archive_entry_mtime(l->entry)));
-		archive_le32enc(&h[FILE_HEADER_CRC32], l->crc32);
-		archive_le32enc(&h[FILE_HEADER_COMPRESSED_SIZE],
-			(uint32_t)l->compressed_size);
-		archive_le32enc(&h[FILE_HEADER_UNCOMPRESSED_SIZE],
-			(uint32_t)archive_entry_size(l->entry));
-		archive_le16enc(&h[FILE_HEADER_FILENAME_LENGTH],
-			(uint16_t)path_length(l->entry));
-		archive_le16enc(&h[FILE_HEADER_EXTRA_LENGTH], sizeof(e));
-		archive_le16enc(&h[FILE_HEADER_ATTRIBUTES_EXTERNAL+2],
-			archive_entry_mode(l->entry));
-		archive_le32enc(&h[FILE_HEADER_OFFSET], (uint32_t)l->offset);
-
-		/* Formatting extra data. */
-		archive_le16enc(&e[EXTRA_DATA_CENTRAL_TIME_ID],
-			ZIP_SIGNATURE_EXTRA_TIMESTAMP);
-		archive_le16enc(&e[EXTRA_DATA_CENTRAL_TIME_SIZE], 1 + 4);
-		e[EXTRA_DATA_CENTRAL_TIME_FLAG] = 0x07;
-		archive_le32enc(&e[EXTRA_DATA_CENTRAL_MTIME],
-			(uint32_t)archive_entry_mtime(l->entry));
-		archive_le16enc(&e[EXTRA_DATA_CENTRAL_UNIX_ID],
-			ZIP_SIGNATURE_EXTRA_NEW_UNIX);
-		archive_le16enc(&e[EXTRA_DATA_CENTRAL_UNIX_SIZE], 0x0000);
-
-		ret = __archive_write_output(a, h, sizeof(h));
+	segment = zip->central_directory;
+	while (segment != NULL) {
+		ret = __archive_write_output(a,
+		    segment->buff, segment->p - segment->buff);
 		if (ret != ARCHIVE_OK)
 			return (ARCHIVE_FATAL);
-		zip->written_bytes += sizeof(h);
-
-		ret = write_path(l->entry, a);
-		if (ret <= ARCHIVE_OK)
-			return (ARCHIVE_FATAL);
-		zip->written_bytes += ret;
+		zip->written_bytes += segment->p - segment->buff;
+		segment = segment->next;
+	}
+	offset_end = zip->written_bytes;
 
-		ret = __archive_write_output(a, e, sizeof(e));
-		if (ret != ARCHIVE_OK)
-			return (ARCHIVE_FATAL);
-		zip->written_bytes += sizeof(e);
+	/* If central dir info is too large, write Zip64 end-of-cd */
+	if (offset_end - offset_start > 0xffffffffLL
+	    || offset_start > 0xffffffffLL
+	    || zip->central_directory_entries > 0xffffUL
+	    || (zip->flags & ZIP_FLAG_FORCE_ZIP64)) {
+	  /* Zip64 end-of-cd record */
+	  memset(buff, 0, 56);
+	  memcpy(buff, "PK\006\006", 4);
+	  archive_le64enc(buff + 4, 44);
+	  archive_le16enc(buff + 12, 45);
+	  archive_le16enc(buff + 14, 45);
+	  /* This is disk 0 of 0. */
+	  archive_le64enc(buff + 24, zip->central_directory_entries);
+	  archive_le64enc(buff + 32, zip->central_directory_entries);
+	  archive_le64enc(buff + 40, offset_end - offset_start);
+	  archive_le64enc(buff + 48, offset_start);
+	  ret = __archive_write_output(a, buff, 56);
+	  if (ret != ARCHIVE_OK)
+		  return (ARCHIVE_FATAL);
+	  zip->written_bytes += 56;
+
+	  /* Zip64 end-of-cd locator record. */
+	  memset(buff, 0, 20);
+	  memcpy(buff, "PK\006\007", 4);
+	  archive_le32enc(buff + 4, 0);
+	  archive_le64enc(buff + 8, offset_end);
+	  archive_le32enc(buff + 16, 1);
+	  ret = __archive_write_output(a, buff, 20);
+	  if (ret != ARCHIVE_OK)
+		  return (ARCHIVE_FATAL);
+	  zip->written_bytes += 20;
 
-		l = l->next;
-		entries++;
 	}
-	offset_end = zip->written_bytes;
 
-	/* Formatting end of central directory. */
-	memset(end, 0, sizeof(end));
-	archive_le32enc(&end[CENTRAL_DIRECTORY_END_SIGNATURE],
-		ZIP_SIGNATURE_CENTRAL_DIRECTORY_END);
-	archive_le16enc(&end[CENTRAL_DIRECTORY_END_ENTRIES_DISK], entries);
-	archive_le16enc(&end[CENTRAL_DIRECTORY_END_ENTRIES], entries);
-	archive_le32enc(&end[CENTRAL_DIRECTORY_END_SIZE],
-		(uint32_t)(offset_end - offset_start));
-	archive_le32enc(&end[CENTRAL_DIRECTORY_END_OFFSET],
-		(uint32_t)offset_start);
-
-	/* Writing end of central directory. */
-	ret = __archive_write_output(a, end, sizeof(end));
+	/* Format and write end of central directory. */
+	memset(buff, 0, sizeof(buff));
+	memcpy(buff, "PK\005\006", 4);
+	archive_le16enc(buff + 8, zipmin(0xffffU, zip->central_directory_entries));
+	archive_le16enc(buff + 10, zipmin(0xffffU, zip->central_directory_entries));
+	archive_le32enc(buff + 12, (uint32_t)zipmin(0xffffffffLL, (offset_end - offset_start)));
+	archive_le32enc(buff + 16, (uint32_t)zipmin(0xffffffffLL, offset_start));
+	ret = __archive_write_output(a, buff, 22);
 	if (ret != ARCHIVE_OK)
 		return (ARCHIVE_FATAL);
-	zip->written_bytes += sizeof(end);
+	zip->written_bytes += 22;
 	return (ARCHIVE_OK);
 }
 
 static int
 archive_write_zip_free(struct archive_write *a)
 {
 	struct zip *zip;
-	struct zip_file_header_link *l;
+	struct cd_segment *segment;
 
 	zip = a->format_data;
 	while (zip->central_directory != NULL) {
-	   l = zip->central_directory;
-	   zip->central_directory = l->next;
-	   archive_entry_free(l->entry);
-	   free(l);
+		segment = zip->central_directory;
+		zip->central_directory = segment->next;
+		free(segment->buff);
+		free(segment);
 	}
 #ifdef HAVE_ZLIB_H
 	free(zip->buf);
 #endif
+	archive_entry_free(zip->entry);
+	/* TODO: Free opt_sconv, sconv_default */
+
 	free(zip);
 	a->format_data = NULL;
 	return (ARCHIVE_OK);
@@ -918,7 +1079,7 @@ write_path(struct archive_entry *entry, struct archive_write *archive)
 		return (ARCHIVE_FATAL);
 	written_bytes += strlen(path);
 
-	/* Folders are recognized by a traling slash. */
+	/* Folders are recognized by a trailing slash. */
 	if ((type == AE_IFDIR) & (path[strlen(path) - 1] != '/')) {
 		ret = __archive_write_output(archive, "/", 1);
 		if (ret != ARCHIVE_OK)
@@ -928,3 +1089,38 @@ write_path(struct archive_entry *entry, struct archive_write *archive)
 
 	return ((int)written_bytes);
 }
+
+static void
+copy_path(struct archive_entry *entry, unsigned char *p)
+{
+	const char *path;
+	size_t pathlen;
+	mode_t type;
+
+	path = archive_entry_pathname(entry);
+	pathlen = strlen(path);
+	type = archive_entry_filetype(entry);
+
+	memcpy(p, path, pathlen);
+
+	/* Folders are recognized by a trailing slash. */
+	if ((type == AE_IFDIR) & (path[pathlen - 1] != '/')) {
+		p[pathlen] = '/';
+		p[pathlen + 1] = '\0';
+	}
+}
+
+
+static struct archive_string_conv *
+get_sconv(struct archive_write *a, struct zip *zip)
+{
+	if (zip->opt_sconv != NULL)
+		return (zip->opt_sconv);
+
+	if (!zip->init_default_conversion) {
+		zip->sconv_default =
+		    archive_string_default_conversion_for_write(&(a->archive));
+		zip->init_default_conversion = 1;
+	}
+	return (zip->sconv_default);
+}